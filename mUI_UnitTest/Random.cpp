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
	delete random_;
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
	int arbitrary_upper_bound = 20;
	for (int i = 0; i < 10; ++i)
	{
		ASSERT_GT(arbitrary_upper_bound, random_->Next(arbitrary_upper_bound));
	}
}

TEST_F(RandomTest, Next_WithUpperAndLowerBound)
{
	int arbitrary_upper_bound = 20;
	int arbitrary_lower_bound = 19;
	for (int i = 0; i < 10; ++i)
	{
		int random_value = random_->Next(arbitrary_lower_bound, arbitrary_upper_bound);
		ASSERT_GT(arbitrary_upper_bound, random_value);
		ASSERT_LE(arbitrary_lower_bound, random_value);
	}
}
