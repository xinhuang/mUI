#include <gtest/gtest.h>
#include <mUI.h>

using mUI::System::String;

class StringTest : public testing::Test
{
public:
	virtual void SetUp()
	{
		string_ = new String();
	}
	virtual void TearDown()
	{
		delete string_;
		string_ = NULL;
	}

protected:
	String *string_;
};

TEST_F(StringTest, Constructor_WhenTypical)
{
	ASSERT_FALSE(NULL == string_);
}

