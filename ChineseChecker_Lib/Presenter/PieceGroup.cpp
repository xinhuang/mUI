#include "PieceGroup.h"

#include "Piece.h"

using std::vector;

struct PieceGroup::Data
{
	int id;
	vector<Piece*> pieces;
};

PieceGroup::PieceGroup( int id ) : _d(new Data())
{
	_d->id = id;
	CreatePieces(PieceMax);
}

PieceGroup::~PieceGroup()
{
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
		_d->pieces[i] = new Piece();
	}
}

