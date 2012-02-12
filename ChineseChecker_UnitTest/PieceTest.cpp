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
		_sut = new Piece(Id);
	}
	virtual void TearDown()
	{
		delete _sut; _sut = nullptr;
	}

protected:
	static const int Id = 2;
	Piece* _sut;
};

TEST_F(PieceTest, Constructor_Typical)
{
	Piece* sut = new Piece(Id);

	ASSERT_NE(nullptr, sut);
	ASSERT_EQ(Id, sut->get_Id());

	delete sut;
}

TEST_F(PieceTest, MoveTo_WhenNoPrevSquare)
{
	SquareMock square;
	EXPECT_CALL(square, set_Piece(_sut)).Times(1);

	_sut->MoveTo(&square);

	ASSERT_EQ(&square, _sut->get_Square());
}

