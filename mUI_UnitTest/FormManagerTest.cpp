#include <gtest/gtest.h>
using namespace testing;

#include <mUI.h>
using namespace mUI;
using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;

#include <System.Forms/FormManager.h>

#include "mocks/MockControl.h"
#include "mocks/MockForm.h"

class FormManagerTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		_sut = &FormManager::get_Instance();
	}

	virtual void TearDown()
	{
		FormManager::Dispose();
		FormManager::Initialize();
	}

	Form* CreateForm(const Point& location)
	{
		Form* form = new Form();
		form->set_Size(Size(100, 100));
		form->set_Location(location);
		return form;
	}

	Control* CreateControl(const Point& location)
	{
		Control* control = new Control();
		control->set_Size(Size(10, 10));
		control->set_Location(location);
		return control;
	}

	MockControl* CreateMockControl()
	{
		return new NiceMock<MockControl>();
	}

	MockForm* CreateMockForm()
	{
		return new NiceMock<MockForm>();
	}

	void Mock_Control_WhenSetFocused(MockControl& control)
	{
		InSequence sequence;
		EXPECT_CALL(control, OnEnter(&EventArgs::Empty));
		EXPECT_CALL(control, OnGotFocus(&EventArgs::Empty));
	}

	void Mock_Control_WhenLoseFocus(MockControl& control)
	{
		InSequence sequence;
		EXPECT_CALL(control, OnLostFocus(&EventArgs::Empty));
		EXPECT_CALL(control, OnLeave(&EventArgs::Empty));
		EXPECT_CALL(control, OnValidating(&EventArgs::Empty));
		EXPECT_CALL(control, OnValidated(&EventArgs::Empty));
	}

	void Mock_Form_WhenSetFocused(MockForm& form)
	{
		InSequence sequence;
		EXPECT_CALL(form, OnActivated(&EventArgs::Empty));
	}

	void Mock_Form_WhenLoseFocus(MockForm& form)
	{
		InSequence sequence;
		EXPECT_CALL(form, OnDeactivate(&EventArgs::Empty));
	}

protected:
	FormManager* _sut;
};

TEST_F(FormManagerTest, Constructor_Typical)
{
	ASSERT_TRUE(null != _sut);
}

TEST_F(FormManagerTest, MapWindowPoint_WhenTranslateFromFormToScreen)
{
	Point formLocation(100, 100);
	Point offsetPoint(7, 7);
	Form* form = CreateForm(formLocation);

	Point screenPoint = 
		FormManager::get_Instance().MapWindowPoint(form->get_Handle(), null, offsetPoint);

	ASSERT_EQ(formLocation + offsetPoint, screenPoint);
}

TEST_F(FormManagerTest, MapWindowPoint_WhenTranslateFromControlToScreen)
{
	Point offsetPoint(7, 7);
	Point formLocation(100, 100);
	Form* form = CreateForm(formLocation);
	Point ctrlLocation(13, 13);
	Control* control = CreateControl(ctrlLocation);
	form->Controls.Add(*control);

	Point screenPoint = 
		FormManager::get_Instance().MapWindowPoint(control->get_Handle(), null, offsetPoint);

	ASSERT_EQ(formLocation + ctrlLocation + offsetPoint, screenPoint);
}

TEST_F(FormManagerTest, MapWindowPoint_WhenTranslateFromControlToForm)
{
	Point offsetPoint(7, 7);
	Point formLocation(100, 100);
	Form* form = CreateForm(formLocation);
	Point ctrlLocation(13, 13);
	Control* control = CreateControl(ctrlLocation);
	form->Controls.Add(*control);

	Point formPoint = 
		FormManager::get_Instance().MapWindowPoint(control->get_Handle(), form->get_Handle(), offsetPoint);

	ASSERT_EQ(ctrlLocation + offsetPoint, formPoint);
}

TEST_F(FormManagerTest, MapWindowPoint_WhenTranslateFromControlToControl)
{
	Point offsetPoint(7, 7);
	Point formLocation(100, 100);
	Form* form = CreateForm(formLocation);
	Point ctrlLocation(13, 13);
	Control* control = CreateControl(ctrlLocation);
	form->Controls.Add(*control);
	Point ctrl1Location(10, 10);
	Control* control1 = CreateControl(ctrl1Location);
	form->Controls.Add(*control1);

	Point pt = FormManager::get_Instance().MapWindowPoint(control->get_Handle(), 
		control1->get_Handle(), offsetPoint);

	ASSERT_EQ(ctrlLocation + ctrl1Location + offsetPoint, pt);
}

TEST_F(FormManagerTest, GetFocusedHandle_WhenNoForm)
{
	ASSERT_EQ(INVALID_VALUE, _sut->GetFocusedHandle());
}

TEST_F(FormManagerTest, SetFocus_WhenNoPreviousFocusedControl)
{
	MockControl* control = CreateMockControl();
	Mock_Control_WhenSetFocused(*control);

	_sut->SetFocus(control->get_Handle());

	ASSERT_EQ(control->get_Handle(), _sut->GetFocusedHandle());

	delete control;
}

TEST_F(FormManagerTest, SetFocus_WhenPreviousFocusedControlExists)
{
	MockControl* prevControl = CreateMockControl();
	_sut->SetFocus(prevControl->get_Handle());
	Mock_Control_WhenLoseFocus(*prevControl);
	MockControl* focusedControl = CreateMockControl();
	Mock_Control_WhenSetFocused(*focusedControl);

	_sut->SetFocus(focusedControl->get_Handle());

	ASSERT_EQ(focusedControl->get_Handle(), _sut->GetFocusedHandle());

	delete prevControl;
	delete focusedControl;
}

TEST_F(FormManagerTest, SetFocus_WhenHandleIsInvalid)
{
	MockControl* control = CreateMockControl();
	_sut->SetFocus(control->get_Handle());

	try 
	{
		_sut->SetFocus(INVALID_VALUE);
	}
	catch (ArgumentException*)
	{
		ASSERT_EQ(control->get_Handle(), _sut->GetFocusedHandle());
		delete control;
		return;
	}

	ASSERT_TRUE(false);
}

TEST_F(FormManagerTest, SetFocus_WhenNoPreviousFocusedForm)
{
	MockForm* form = CreateMockForm();
	Mock_Form_WhenSetFocused(*form);

	_sut->SetFocus(form->get_Handle());

	ASSERT_EQ(form->get_Handle(), _sut->GetFocusedHandle());

	delete form;
}

TEST_F(FormManagerTest, SetFocus_WhenPreviousFocusedFormExists)
{
	MockForm* prevForm = CreateMockForm();
	_sut->SetFocus(prevForm->get_Handle());
	Mock_Form_WhenLoseFocus(*prevForm);
	MockForm* focusedForm = CreateMockForm();
	Mock_Form_WhenSetFocused(*focusedForm);

	_sut->SetFocus(focusedForm->get_Handle());

	ASSERT_EQ(focusedForm->get_Handle(), _sut->GetFocusedHandle());

	delete prevForm;
	delete focusedForm;
}

TEST_F(FormManagerTest, SetFocus_WhenNoPreviousFocusAndFocusOnControlInForm)
{
	MockForm* containerForm = CreateMockForm();
	MockControl* focusControl = CreateMockControl();
	containerForm->Controls.Add(*focusControl);

	_sut->SetFocus(focusControl->get_Handle());

	ASSERT_EQ(focusControl->get_Handle(), _sut->GetFocusedHandle());

	delete containerForm;
}
