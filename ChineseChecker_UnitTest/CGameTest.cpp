#include <Presenter/CGame.h>

#include <gtest/gtest.h>

#include <Presenter/Player.h>
#include <Presenter/Board.h>
#include <Presenter/Square.h>

#include "mocks/BoardMock.h"

class TestableCGame : public CGame
{
public:
	using CGame::get_CurrentPlayerIndex;
	using CGame::TakeTurn;
};

class CGameTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		_boardMock = new BoardMock();
		_sut = (TestableCGame*)new CGame();
		_savedBoard = _sut->get_Board();
		_sut->set_Board(_boardMock);
		_sut->set_PlayerTotal(2);
		_sut->set_PlayerGroupId(0, Color::Black);
		_sut->set_PlayerGroupId(1, Color::White);
	}
	virtual void TearDown()
	{
		_sut->set_Board(_savedBoard);
		delete _sut;
		delete _boardMock;
	}

protected:
	TestableCGame* _sut;
	BoardMock* _boardMock;
	Board* _savedBoard;
};

TEST_F(CGameTest, Constructor_Typical)
{
	CGame* sut = new CGame();

	ASSERT_NE(nullptr, sut);
	ASSERT_NE(nullptr, sut->get_Board());
	for (int i = 0; i < CGame::PieceGroupTotal; ++i)
		ASSERT_NE(nullptr, _sut->GetPieceGroup(i));

	delete sut;
}

TEST_F(CGameTest, NewGame_Typical)
{
	EXPECT_CALL(*_boardMock, Reset()).Times(1);

	_sut->NewGame();

    Player* p0 = _sut->PlayerAt(0);
    Player* p1 = _sut->PlayerAt(1);
	ASSERT_NE(nullptr, p0);
    ASSERT_NE(nullptr, p1);
    ASSERT_TRUE(p0->Owns(Color::Black));
    ASSERT_FALSE(p0->Owns(Color::White));
    ASSERT_FALSE(p1->Owns(Color::Black));
    ASSERT_TRUE(p1->Owns(Color::White));
}

TEST_F(CGameTest, TakeTurn_Typical)
{
	_sut->NewGame();

	_sut->TakeTurn(0);

	ASSERT_EQ(0, _sut->get_CurrentPlayerIndex());
	ASSERT_EQ(_sut->PlayerAt(0), _sut->get_CurrentPlayer());
}

TEST_F(CGameTest, MovePiece_WhenMoveToAdjacentSquare)
{
	_sut->NewGame();
	auto board = _sut->get_Board();
	auto fromSquare = board->SquareAt(Point(8, 8));
	auto toSquare = board->SquareAt(Point(8, 9));
	Piece* piece = board->SquareAt(Point(4, 0))->get_Piece();
	piece->MoveTo(fromSquare);

	_sut->MovePiece(Point(8, 8), Point(8, 9));
}
