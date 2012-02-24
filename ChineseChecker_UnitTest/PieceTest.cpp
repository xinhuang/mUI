#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;
using ::testing::NiceMock;

#include "mocks/PieceMock.h"
#include "mocks/BoardMock.h"
#include "mocks/SquareMock.h"

#include <Presenter/Piece.h>

class PieceTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		_board = new BoardMock();
		_sut = new Piece(_board, Id);
	}
	virtual void TearDown()
	{
		delete _sut; _sut = nullptr;
		delete _board; _board = nullptr;
	}

protected:
	static const int Id = 2;
	Piece* _sut;
	BoardMock* _board;
	SquareMock* _locSquare;
};

TEST_F(PieceTest, Constructor_Typical)
{
	Piece* sut = new Piece(nullptr, Id);

	ASSERT_NE(nullptr, sut);
	ASSERT_EQ(Id, sut->get_Id());

	delete sut;
}

TEST_F(PieceTest, MoveTo_WhenNoPrevSquare)
{
	NiceMock<SquareMock> square;
	EXPECT_CALL(square, set_Piece(_sut)).Times(1);

	_sut->MoveTo(&square);

	ASSERT_EQ(&square, _sut->get_Square());
}

