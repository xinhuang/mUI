#include "Piece.h"

#include "Square.h"

#include <cassert>

struct Piece::Data
{
	Square* square;
};

Piece::Piece() : _d(new Data())
{
	_d->square = nullptr;
}

Piece::~Piece()
{
	delete _d;
}

void Piece::MoveTo( Square* square )
{
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
}

const Square* Piece::get_Square() const
{
	return _d->square;
}

Square* Piece::get_Square()
{
	return _d->square;
}
