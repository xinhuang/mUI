#include "Square.h"
#include "Piece.h"

struct Square::Data
{
	Piece* piece;
};

Square::Square()
	: _d(new Data())
{}

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
