#include <gtest/gtest.h>

#include <mUI.h>
using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;

#include <System.Forms/FormManager.h>

void CreateControl();

void CreateForm();

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