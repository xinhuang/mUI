#include "CGame.h"

#include "Board.h"

struct CGame::Data
{
	Data()
		: board(new Board())
	{}
	~Data()
	{
		delete board;
	}

	Board* board;
};

CGame::CGame() : _d(new Data)
{

}

CGame::~CGame()
{
	delete _d;
}

Board* CGame::get_Board()
{
	return _d->board;
}

