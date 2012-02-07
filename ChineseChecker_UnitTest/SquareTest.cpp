#include <gtest/gtest.h>

#include <Presenter/Square.h>

class SquareTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		_square = new Square();
	}

	virtual void TearDown()
	{
		delete _square; _square = NULL;
	}

protected:
	Square* _square;
};

TEST_F(SquareTest, Constructor_Typical)
{
	ASSERT_TRUE(NULL != _square);
}

TEST_F(SquareTest, get_IsOccupied_WhenDefault)
{
	ASSERT_FALSE(_square->get_IsOccupied());
}

TEST_F(SquareTest, get_Piece_WhenDefault)
{
	ASSERT_TRUE(NULL == _square->get_Piece());
}
