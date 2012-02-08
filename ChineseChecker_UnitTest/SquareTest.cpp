#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;

#include "mocks/PieceMock.h"

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
		delete _square; _square = nullptr;
	}

protected:
	Square* _square;
};

TEST_F(SquareTest, Constructor_Typical)
{
	ASSERT_TRUE(nullptr != _square);
}

TEST_F(SquareTest, get_Piece_WhenDefault)
{
	ASSERT_TRUE(nullptr == _square->get_Piece());
}

TEST_F(SquareTest, set_Piece_WhenPrevSquareIsNull)
{
	PieceMock piece;
	EXPECT_CALL(piece, get_Square()).WillOnce(Return(nullptr));
	_square->set_Piece(&piece);

	ASSERT_EQ(&piece, _square->get_Piece());
}
