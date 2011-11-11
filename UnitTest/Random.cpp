#include <gtest/gtest.h>
#include <mUI.h>

using mUI::System::Random;

class RandomTest : public testing::Test
{
public:
	virtual void SetUp()
	{
		random_ = new Random();
	}
	virtual void TearDown()
	{
		delete random_;
	}

private:
	Random* random_;
};

TEST_F(RandomTest, Constructor_WhenTypical)
{
}
