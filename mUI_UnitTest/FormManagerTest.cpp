#include <gtest/gtest.h>

#include <mUI.h>
using namespace mUI;
using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;

#include <System.Forms/FormManager.h>

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

TEST_F(FormManagerTest, SetFocus_Typical)
{
	Form* form = CreateForm(Point::Empty);

	_sut->SetFocus(form->get_Handle());

	ASSERT_EQ(form->get_Handle(), _sut->GetFocusedHandle());
}
