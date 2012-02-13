#include <Presenter/CGame.h>

#include <gmock/gmock.h>
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::Return;
using ::testing::_;

#include <Presenter/Player.h>
#include <Presenter/Board.h>
#include <Presenter/Square.h>

#include "mocks/BoardMock.h"
#include "mocks/PieceGroupMock.h"
#include "mocks/SquareMock.h"
#include "mocks/PieceMock.h"

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
		_sut = (TestableCGame*)new CGame();

		_boardMock = nullptr;
		_pieceGroupMock = nullptr;
		_squareMock = nullptr;
		_pieceMock = nullptr;
		SaveSutState();
		InstallNiceMock();

		_sut->set_PlayerTotal(2);
		_sut->set_PlayerGroupId(0, 0);
		_sut->set_PlayerGroupId(1, 1);

		_fromPoint = Point(4, 4);
		_toPoint = Point(5, 5);
	}

	void InstallNiceMock();
	void InstallStrictMock();
	void SaveSutState();

	virtual void TearDown()
	{
		UninstallMock();
		delete _sut;
	}

	void UninstallMock();

protected:
	TestableCGame* _sut;
	BoardMock* _boardMock;
	Board* _savedBoard;
	PieceGroupMock* _pieceGroupMock;
	vector<PieceGroup*> _savedPieceGroups;
	SquareMock* _squareMock;
	PieceMock* _pieceMock;
	Point _fromPoint;
	Point _toPoint;
};

void CGameTest::InstallNiceMock()
{
	UninstallMock();

	_boardMock = new NiceMock<BoardMock>();
	_pieceGroupMock = new NiceMock<PieceGroupMock>();
	_squareMock = new NiceMock<SquareMock>();
	_pieceMock = new NiceMock<PieceMock>();

	EXPECT_CALL(*_boardMock, SquareAt(_)).WillRepeatedly(Return(_squareMock));
	_sut->set_Board(_boardMock);

	_savedPieceGroups.resize(CGame::PieceGroupTotal);
	for (int i = 0; i < CGame::PieceGroupTotal; ++i)
	{
		_sut->SetPieceGroup(i, _pieceGroupMock);
	}
	_pieceGroupMock = new PieceGroupMock();
}

void CGameTest::InstallStrictMock()
{
	UninstallMock();

	_boardMock = new StrictMock<BoardMock>();
	_squareMock = new NiceMock<SquareMock>();
	_pieceGroupMock = new StrictMock<PieceGroupMock>();
	_pieceMock = new NiceMock<PieceMock>();

	EXPECT_CALL(*_boardMock, SquareAt(_)).WillRepeatedly(Return(_squareMock));
	_sut->set_Board(_boardMock);

	_savedPieceGroups.resize(CGame::PieceGroupTotal);
	for (int i = 0; i < CGame::PieceGroupTotal; ++i)
	{
		_sut->SetPieceGroup(i, _pieceGroupMock);
	}
}

void CGameTest::UninstallMock()
{
	_sut->set_Board(_savedBoard);
	delete _boardMock;

	for (int i = 0; i < CGame::PieceGroupTotal; ++i)
	{
		_sut->SetPieceGroup(i, _savedPieceGroups[i]);
	}
	delete _pieceGroupMock;

	delete _squareMock;
	delete _pieceMock;
}

void CGameTest::SaveSutState()
{
	_savedBoard = _sut->get_Board();

	_savedPieceGroups.resize(CGame::PieceGroupTotal);
	for (int i = 0; i < CGame::PieceGroupTotal; ++i)
	{
		_savedPieceGroups[i] = _sut->GetPieceGroup(i);
	}
}

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
	InstallStrictMock();
	EXPECT_CALL(*_pieceGroupMock, Reset()).Times(CGame::PieceGroupTotal);

	_sut->NewGame();

    Player* p0 = _sut->PlayerAt(0);
    Player* p1 = _sut->PlayerAt(1);
	ASSERT_NE(nullptr, p0);
    ASSERT_NE(nullptr, p1);
    ASSERT_TRUE(p0->Owns(0));
    ASSERT_FALSE(p0->Owns(1));
    ASSERT_FALSE(p1->Owns(0));
    ASSERT_TRUE(p1->Owns(1));
}

TEST_F(CGameTest, TakeTurn_Typical)
{
	size_t playerId = 1;
	_sut->NewGame();

	_sut->TakeTurn(playerId);

	ASSERT_EQ(playerId, _sut->get_CurrentPlayerIndex());
	ASSERT_EQ(_sut->PlayerAt(playerId), _sut->get_CurrentPlayer());
}

TEST_F(CGameTest, MovePiece_Typical)
{
	_sut->NewGame();
	_sut->TakeTurn(0);
	EXPECT_CALL(*_pieceMock, get_Id()).WillRepeatedly(Return(0));
	EXPECT_CALL(*_squareMock, get_Piece()).WillOnce(Return(_pieceMock));
	EXPECT_CALL(*_boardMock, MovePiece(_, _))
		.Times(1).WillOnce(Return(true));

	bool result = _sut->MovePiece(_fromPoint, _toPoint);

	ASSERT_TRUE(result);
}

TEST_F(CGameTest, MovePiece_WhenFromSquareIsEmpty)
{
	_sut->NewGame();
	EXPECT_CALL(*_squareMock, get_Piece()).WillOnce(Return(nullptr));
	EXPECT_CALL(*_boardMock, MovePiece(_, _)).Times(0);

	bool result = _sut->MovePiece(_fromPoint, _toPoint);

	ASSERT_FALSE(result);
}

TEST_F(CGameTest, MovePiece_WhenPieceIsNotOwned)
{
	_sut->NewGame();
	_sut->TakeTurn(0);
	EXPECT_CALL(*_pieceMock, get_Id()).WillRepeatedly(Return(1));
	EXPECT_CALL(*_squareMock, get_Piece()).WillOnce(Return(_pieceMock));
	EXPECT_CALL(*_boardMock, MovePiece(_, _)).Times(0);

	bool result = _sut->MovePiece(_fromPoint, _toPoint);

	ASSERT_FALSE(result);
}
