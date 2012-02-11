#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;

#include "mocks/PieceMock.h"
#include "mocks/SquareMock.h"

#include <Presenter/Piece.h>

class PieceTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		_sut = new Piece();
	}
	virtual void TearDown()
	{
		delete _sut; _sut = nullptr;
	}

protected:
	Piece* _sut;
};

TEST_F(PieceTest, Constructor_Typical)
{
	Piece* sut = new Piece();

	ASSERT_NE(nullptr, sut);

	delete sut;
}

TEST_F(PieceTest, MoveTo_WhenNoPrevSquare)
{
	SquareMock square;
	EXPECT_CALL(square, set_Piece(_sut)).Times(1);

	_sut->MoveTo(&square);

	ASSERT_EQ(&square, _sut->get_Square());
}

