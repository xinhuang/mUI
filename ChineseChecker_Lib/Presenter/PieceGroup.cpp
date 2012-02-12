#include "PieceGroup.h"

#include "Piece.h"
#include "Board.h"

using std::vector;

struct PieceGroup::Data
{
	int id;
	Board* board;
	Point fromLocation;
	Point goalLocation;
	vector<Piece*> pieces;
};

PieceGroup::PieceGroup( int id, Board* board, 
	const Point& fromLocation, const Point& goalLocation ) 
	: _d(new Data())
{
	_d->id = id;
	_d->board = board;
	_d->fromLocation = fromLocation;
	_d->goalLocation = goalLocation;
	CreatePieces(PieceMax);
}

PieceGroup::~PieceGroup()
{
	while (!_d->pieces.empty())
	{
		delete _d->pieces.back();
		_d->pieces.pop_back();
	}
	delete _d;
}

vector<Piece*>& PieceGroup::get_Pieces()
{
	return _d->pieces;
}

int PieceGroup::get_Id() const
{
	return _d->id;
}

void PieceGroup::CreatePieces( int pieceTotal )
{
	_d->pieces.resize(pieceTotal);
	for (int i = 0; i < pieceTotal; ++i)
	{
		_d->pieces[i] = new Piece(get_Id());
	}
}

std::vector<Square*> PieceGroup::get_StartSquares()
{
	return _d->board->GetGoalSquares(_d->fromLocation);
}

void PieceGroup::Reset()
{
}

