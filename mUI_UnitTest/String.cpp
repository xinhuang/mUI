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

TEST_F(StringTest, Constructor_WhenConstructUsingWcharArray)
{
	const wchar_t* init_wstring = L"ArbitraryString";
	wchar_t check_for_const[128];
	wcscpy(check_for_const, init_wstring);
	
	string_ = new String(init_wstring);

	ASSERT_EQ(init_wstring, *string_);
	ASSERT_STREQ(check_for_const, init_wstring);
	ASSERT_EQ(check_for_const, *string_);
}

