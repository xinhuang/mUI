#include "CGame.h"

#include "Board.h"
#include "Player.h"

struct CGame::Data
{
	Board* board;
	size_t playerTotal;
	vector<Player*> players;
    map<size_t, vector<Color>> colorMap;
};

CGame::CGame() : _d(new Data)
{
	_d->board = new Board();
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

}

size_t CGame::get_CurrentPlayerIndex() const
{
	return 0;
}

void CGame::set_PlayerTotal( size_t playerTotal )
{
	_d->playerTotal = playerTotal;
}

void CGame::NewGame()
{
	while (!_d->players.empty())
	{
		delete _d->players.back();
		_d->players.pop_back();
	}
	_d->players.resize(_d->playerTotal);
	for (size_t i = 0; i < _d->playerTotal; ++i)
	{
		_d->players[i] = new Player(_d->colorMap[i]);
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

void CGame::set_PlayerColor(size_t playerNumber, const Color& color)
{
    auto playerColor = _d->colorMap.find(playerNumber);
    if (playerColor == _d->colorMap.end())
    {
        _d->colorMap.insert(make_pair(playerNumber, vector<Color>(1, color)));
        return;
    }
    else
    {
        playerColor->second.clear();
        playerColor->second.push_back(color);
    }
}
