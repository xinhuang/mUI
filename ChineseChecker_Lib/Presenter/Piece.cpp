#include "Piece.h"

#include "Square.h"

#include <cassert>

#include "Board.h"

struct Piece::Data
{
	Data(int id) : id(id) {}

	const int id;
	Square* square;
	Board* board;
};

Piece::Piece(Board* board, int id) : _d(new Data(id))
{
	_d->square = nullptr;
	_d->board = board;
}

Piece::~Piece()
{
	delete _d;
}

bool Piece::MoveTo( Square* square )
{
	if (square != nullptr && _d->square != nullptr 
		&& !_d->board->IsAccessible(*get_Square(), *square))
		return false;
	if (_d->square != nullptr)
	{
		assert(this == _d->square->get_Piece());
		_d->square->set_Piece(nullptr);
	}
	if (square != nullptr)
	{
		assert(nullptr == square->get_Piece());
		square->set_Piece(this);
	}
	_d->square = square;
	return true;
}

const Square* Piece::get_Square() const
{
	return _d->square;
}

Square* Piece::get_Square()
{
	return _d->square;
}

int Piece::get_Id() const
{
	return _d->id;
}
