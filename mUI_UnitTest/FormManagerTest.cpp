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
	ASSERT_TRUE(NULL != _sut);
}
