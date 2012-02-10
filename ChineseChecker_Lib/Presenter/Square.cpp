#include "Square.h"
#include "Piece.h"

struct Square::Data
{
	Data()
		: piece(nullptr)
	{}

	Piece* piece;
	Point location;
};

Square::Square(const Point& location)
	: _d(new Data())
{
	_d->location = location;
}

Square::~Square()
{
	delete _d;
}

void Square::set_Piece( Piece* piece )
{
	if (piece == nullptr)
	{
		_d->piece = nullptr;
		return;
	}

	Square* originSquare = piece->get_Square();
	if (originSquare != nullptr)
	{
		originSquare->set_Piece(nullptr);
	}
	_d->piece = piece;
}

const Piece* Square::get_Piece() const
{
	return _d->piece;
}

const Point& Square::get_Location() const
{
	return _d->location;
}
