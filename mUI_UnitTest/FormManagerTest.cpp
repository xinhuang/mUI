#include <gtest/gtest.h>

#include <mUI.h>
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
	Form* container = new Form();
	container->set_Size(Size(100, 100));
	container->set_Location(formLocation);

	Point screenPoint = 
		FormManager::get_Instance().MapWindowPoint(container->get_Handle(), null, offsetPoint);

	ASSERT_EQ(formLocation + offsetPoint, screenPoint);
}

TEST_F(FormManagerTest, MapWindowPoint_WhenTranslateFromControlToScreen)
{
	Point offsetPoint(7, 7);
	Point formLocation(100, 100);
	Form* container = new Form();
	container->set_Size(Size(100, 100));
	container->set_Location(formLocation);
	Point elementLocation(13, 13);
	Control* element = new Control();
	element->set_Size(Size(10, 10));
	element->set_Location(elementLocation);
	container->Controls.Add(*element);

	Point screenPoint = 
		FormManager::get_Instance().MapWindowPoint(element->get_Handle(), null, offsetPoint);

	ASSERT_EQ(formLocation + elementLocation + offsetPoint, screenPoint);
}
