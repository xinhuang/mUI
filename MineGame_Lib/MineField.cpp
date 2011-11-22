#include "MineField.h"
#include <mUI.h>

#include "MGame.h"
#include "BlankSquare.h"

MineField::MineField(MGame* game)
	: _MGame(game)
{
	CreateSquares();
}

MineField::~MineField()
{
	for (size_t i = 0; i < _squares.size(); ++i)
		delete _squares[i];
	_squares.clear();
}

void MineField::CreateSquares()
{
	for (int r = 0; r < get_Size().Width; ++r)
	{
		for (int c = 0; c < get_Size().Height; ++c)
		{
			_squares.push_back(new BlankSquare(_MGame, this, r, c));
		}
	}
}

const Size& MineField::get_Size() const
{
	return _MGame->get_MineFieldSize();
}

int MineField::get_MineTotal() const
{
	return _MGame->get_MineTotal();
}

ISquare* MineField::SquareAt(int row, int column)
{
	return _squares.at(row * get_Size().Width + column);
}
