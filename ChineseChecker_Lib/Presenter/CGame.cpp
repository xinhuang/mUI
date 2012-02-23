#include "CGame.h"

#include "Board.h"
#include "Player.h"
#include "PieceGroup.h"
#include "Square.h"

struct CGame::Data
{
	Board* board;
	vector<PieceGroup*> pieceGroups;
	size_t playerTotal;
	size_t currentPlayerIndex;
	vector<Player*> players;
    PlayerIdMap idMap;
	Piece* picked;
};

CGame::CGame() : _d(new Data)
{
	_d->board = new Board();

	_d->pieceGroups.resize(CGame::PieceGroupTotal);
	for (int i = 0; i < CGame::PieceGroupTotal; ++i)
		_d->pieceGroups[i] = new PieceGroup(i, _d->board, Point::Empty, Point::Empty);

	_d->picked = nullptr;
}

CGame::~CGame()
{
	delete _d->board;
	delete _d;
}

Board* CGame::get_Board()
{
	return _d->board;
}

void CGame::TakeTurn( int playerIndex )
{
	_d->currentPlayerIndex = playerIndex;
}

size_t CGame::get_CurrentPlayerIndex() const
{
	return _d->currentPlayerIndex;
}

void CGame::set_PlayerTotal( size_t playerTotal )
{
	_d->playerTotal = playerTotal;
}

void CGame::NewGame()
{
	CreatePlayers(_d->idMap);
	for (int i = 0; i < PieceGroupTotal; ++i)
	{
		GetPieceGroup(i)->Reset();
	}
}

Player* CGame::PlayerAt( size_t playerNumber )
{
	return _d->players[playerNumber];
}

Player* CGame::get_CurrentPlayer()
{
	return PlayerAt(get_CurrentPlayerIndex());
}

void CGame::set_PlayerGroupId(size_t playerNumber, int id)
{
    auto playerColor = _d->idMap.find(playerNumber);
    if (playerColor == _d->idMap.end())
        _d->idMap[playerNumber] = vector<int>(1, id);
    else
        playerColor->second.resize(1, id);
}

bool CGame::MovePiece( const Point& from, const Point& to )
{
	auto fromSquare = _d->board->SquareAt(from);
	auto toSquare = _d->board->SquareAt(to);
	assert(fromSquare != nullptr);
	assert(toSquare != nullptr);
	auto piece = fromSquare->get_Piece();
	if (piece != nullptr && get_CurrentPlayer()->Owns(piece->get_Id()))
		return _d->board->MovePiece(*fromSquare, *toSquare);
	else
		return false;
}

PieceGroup* CGame::GetPieceGroup( int groupId )
{
	return _d->pieceGroups[groupId];
}
void CGame::SetPieceGroup( int groupId, PieceGroup* pieceGroup )
{
	_d->pieceGroups[groupId] = pieceGroup;
}

void CGame::set_Board( Board* board )
{
	_d->board = board;
}

void CGame::CreatePlayers(const PlayerIdMap& idMap)
{
	while (!_d->players.empty())
	{
		delete _d->players.back();
		_d->players.pop_back();
	}
	_d->players.resize(_d->playerTotal);
	for (size_t i = 0; i < _d->playerTotal; ++i)
	{
		_d->players[i] = new Player(idMap.at(i));
	}
}

Piece* CGame::get_Picked()
{
	return _d->picked;
}

void CGame::Pick( Piece* piece )
{
	_d->picked = piece;
}
