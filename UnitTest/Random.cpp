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

protected:
	Random* random_;
};

TEST_F(RandomTest, Constructor_WhenTypical)
{
	ASSERT_FALSE(NULL == random_);
}

TEST_F(RandomTest, Constructor_SameSeedSameSequence)
{
	int arbitrary_seed = 10;
	random_ = new Random(arbitrary_seed);
	Random comparison(arbitrary_seed);

	for (int i = 0; i < 10; ++i)
		ASSERT_EQ(comparison.Next(), random_->Next());
}

TEST_F(RandomTest, Next_WhenTypical)
{
	int first_value = random_->Next();
	for (int i = 0; i < 10; ++i)
	{
		if (first_value != random_->Next())
			return;
	}
	ASSERT_FALSE(true);
}

TEST_F(RandomTest, Next_WithUpperBound)
{
}
