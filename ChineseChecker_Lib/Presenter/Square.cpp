#include "Square.h"
#include "Piece.h"
#include "CGame.h"

struct Square::Data
{
	Data()
		: piece(nullptr)
	{}

	Piece* piece;
	Point location;
	CGame* game;
};

Square::Square(CGame* game, const Point& location)
	: _d(new Data())
{
	_d->location = location;
	_d->game = game;
}

Square::~Square()
{
	delete _d;
}

void Square::set_Piece( Piece* piece )
{
	_d->piece = piece;
}

Piece* Square::get_Piece()
{
	return _d->piece;
}

const Piece* Square::get_Piece() const
{
	return _d->piece;
}

const Point& Square::get_Location() const
{
	return _d->location;
}

void Square::OnMouseClick( void* sender, MouseEventArgs* e )
{
	Piece* picked = _d->game->get_Picked();
	if (picked == get_Piece())
	{
		_d->game->set_Picked(nullptr);
	}
	else
	{
		if (picked != nullptr)
		{
			picked->MoveTo(this);
		}
		_d->game->set_Picked(get_Piece());
	}
}
