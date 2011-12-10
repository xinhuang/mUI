#include <gtest/gtest.h>
#include <mUI.h>

using mUI::System::String;

class StringTest : public testing::Test
{
public:
	virtual void SetUp()
	{
		_sut = L"";
	}

protected:
	String _sut;
};

TEST_F(StringTest, Constructor_WhenTypical)
{
	ASSERT_EQ(L"", _sut);
}

TEST_F(StringTest, Constructor_WhenConstructUsingWcharArray)
{
	const wchar_t* initWstring = L"ArbitraryString";
	wchar_t checkForConst[128];
	wcsncpy_s(checkForConst, initWstring, sizeof(checkForConst)/sizeof(checkForConst[0]));
	
	_sut = initWstring;

	ASSERT_EQ(initWstring, _sut);
	ASSERT_STREQ(checkForConst, initWstring);
	ASSERT_EQ(checkForConst, _sut);
}

