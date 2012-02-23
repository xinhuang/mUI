#include <gmock/gmock.h>
using namespace ::testing;

#include <Presenter/Board.h>
#include <Presenter/Square.h>

#include "mocks/SquareMock.h"
#include "mocks/PieceMock.h"

using namespace std;

#include <mUI.h>
using namespace mUI::System;
using namespace mUI::System::Drawing;

class BoardTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		_sut = new Board();
		_sq0 = new SquareMock();
		_sq1 = new SquareMock();
		_piece = new PieceMock();
	}
	virtual void TearDown()
	{
		delete _sut; _sut = nullptr;
		delete _sq0; _sq0 = nullptr;
		delete _sq1; _sq1 = nullptr;
		delete _piece; _piece = nullptr;
	}

	void VerifySquareLocationsContain(const vector<Square*>& container, const Point& location) const
	{
		for (auto iter = container.begin(); iter != container.end(); ++iter)
			ASSERT_NE(nullptr, *iter);
		for (auto iter = container.begin(); iter != container.end(); ++iter)
			if (location == (*iter)->get_Location())
				return;
		ASSERT_TRUE(false);
	}

protected:
	Board* _sut;
	SquareMock *_sq0;
	SquareMock *_sq1;
	PieceMock *_piece;
};

TEST_F(BoardTest, Constructor_Typical)
{
	Board* sut = new Board();

	ASSERT_TRUE(nullptr != sut);
	for (int x = 0; x < Board::Width; ++x)
	{
		for (int y = 0; y < Board::Height; ++y)
		{
			ASSERT_NE(nullptr, sut->SquareAt(Point(x, y)));
		}
	}

	delete sut;
}

TEST_F(BoardTest, GetSquaresInFormation_Location_0_4)
{
	vector<Square*> goalSquares = _sut->GetSquaresInFormation(Point(0, 4));

	ASSERT_EQ(15, goalSquares.size());
	for (int y = 4; y < 9; ++y)
	{
		for (int x = y - 4; x < 5; ++x)
		{
			VerifySquareLocationsContain(goalSquares, Point(x, y));
		}
	}
}

TEST_F(BoardTest, GetSquaresInFormation_Location_4_0)
{
	vector<Square*> goalSquares = _sut->GetSquaresInFormation(Point(4, 0));

	ASSERT_EQ(15, goalSquares.size());
	for (int x = 4; x < 9; ++x)
	{
		for (int y = x - 4; y < 5; ++y)
		{
			VerifySquareLocationsContain(goalSquares, Point(x, y));
		}
	}
}

TEST_F(BoardTest, GetSquaresInFormation_Location_12_4)
{
	vector<Square*> goalSquares = _sut->GetSquaresInFormation(Point(12, 4));

	ASSERT_EQ(15, goalSquares.size());
	VerifySquareLocationsContain(goalSquares, Point(8, 4));
	VerifySquareLocationsContain(goalSquares, Point(9, 4));
	VerifySquareLocationsContain(goalSquares, Point(10, 4));
	VerifySquareLocationsContain(goalSquares, Point(11, 4));
	VerifySquareLocationsContain(goalSquares, Point(12, 4));
	VerifySquareLocationsContain(goalSquares, Point(9, 5));
	VerifySquareLocationsContain(goalSquares, Point(10, 5));
	VerifySquareLocationsContain(goalSquares, Point(11, 5));
	VerifySquareLocationsContain(goalSquares, Point(12, 5));
	VerifySquareLocationsContain(goalSquares, Point(10, 6));
	VerifySquareLocationsContain(goalSquares, Point(11, 6));
	VerifySquareLocationsContain(goalSquares, Point(12, 6));
	VerifySquareLocationsContain(goalSquares, Point(11, 7));
	VerifySquareLocationsContain(goalSquares, Point(12, 7));
	VerifySquareLocationsContain(goalSquares, Point(12, 8));
}

TEST_F(BoardTest, GetSquaresInFormation_Location_16_12)
{
	vector<Square*> goalSquares = _sut->GetSquaresInFormation(Point(16, 12));

	ASSERT_EQ(15, goalSquares.size());
	for (int x = 12; x < 17; ++x)
	{
		for (int y = 8 + x - 12; y < 13; ++y)
		{
			VerifySquareLocationsContain(goalSquares, Point(x, y));
		}
	}
}

TEST_F(BoardTest, GetSquaresInFormation_Location_12_16)
{
	vector<Square*> goalSquares = _sut->GetSquaresInFormation(Point(12, 16));

	ASSERT_EQ(15, goalSquares.size());
	for (int y = 12; y < 17; ++y)
	{
		for (int x = y - 4; x < 13; ++x)
		{
			VerifySquareLocationsContain(goalSquares, Point(x, y));
		}
	}
}

TEST_F(BoardTest, GetSquaresInFormation_Location_4_12)
{
	vector<Square*> goalSquares = _sut->GetSquaresInFormation(Point(4, 12));

	ASSERT_EQ(15, goalSquares.size());
	for (int x = 4; x < 9; ++x)
	{
		for (int y = x + 4; y < 13; ++y)
		{
			VerifySquareLocationsContain(goalSquares, Point(x, y));
		}
	}
}

TEST_F(BoardTest, GetSquaresInFormation_WhenArgIsNotTopSquare)
{
	EXPECT_THROW(_sut->GetSquaresInFormation(Point(8, 7)), ArgumentException*);
}

TEST_F(BoardTest, SquareAt_WhenTypical)
{
	Point location(4, 0);
	Square* square = _sut->SquareAt(location);
	
	ASSERT_NE(nullptr, square);
	ASSERT_EQ(location, square->get_Location());
}

TEST_F(BoardTest, MovePiece_WhenMoveOneStep)
{
	EXPECT_CALL(*_sq0, get_Piece()).WillRepeatedly(Return(_piece));
	EXPECT_CALL(*_sq1, get_Piece()).WillRepeatedly(Return(nullptr));
	EXPECT_CALL(*_sq0, get_Location()).WillRepeatedly(ReturnRef(Point(4, 0)));
	EXPECT_CALL(*_sq1, get_Location()).WillRepeatedly(ReturnRef(Point(5, 1)));
	EXPECT_CALL(*_piece, MoveTo(_sq1)).Times(1);

	bool result = _sut->MovePiece(*_sq0, *_sq1);

	ASSERT_TRUE(result);
}

TEST_F(BoardTest, MovePiece_WhenMoveTwoStep)
{
	EXPECT_CALL(*_sq0, get_Piece()).WillRepeatedly(Return(_piece));
	EXPECT_CALL(*_sq1, get_Piece()).WillRepeatedly(Return(nullptr));
	EXPECT_CALL(*_sq0, get_Location()).WillRepeatedly(ReturnRef(Point(4, 0)));
	EXPECT_CALL(*_sq1, get_Location()).WillRepeatedly(ReturnRef(Point(6, 2)));
	EXPECT_CALL(*_piece, MoveTo(_sq1)).Times(0);

	bool result = _sut->MovePiece(*_sq0, *_sq1);

	ASSERT_FALSE(result);
}

TEST_F(BoardTest, MovePiece_WhenDestinationIsOccupied)
{
	EXPECT_CALL(*_sq0, get_Piece()).WillRepeatedly(Return(_piece));
	EXPECT_CALL(*_sq1, get_Piece()).WillRepeatedly(Return(_piece));

	bool result = _sut->MovePiece(*_sq0, *_sq1);

	ASSERT_FALSE(result);
}
