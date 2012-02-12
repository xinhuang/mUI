#include "PieceGroup.h"

#include "Piece.h"
#include "Board.h"

using std::vector;

struct PieceGroup::Data
{
	int id;
	Board* board;
	Point startPoint;
	Point goalPoint;
	vector<Piece*> pieces;
};

PieceGroup::PieceGroup( int id, Board* board, 
	const Point& fromLocation, const Point& goalLocation ) 
	: _d(new Data())
{
	_d->id = id;
	_d->board = board;
	_d->startPoint = fromLocation;
	_d->goalPoint = goalLocation;
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
	return _d->board->GetSquaresInFormation(_d->startPoint);
}

void PieceGroup::Reset()
{
	auto startSquares = get_StartSquares();
	assert(startSquares.size() == _d->pieces.size());
	for (size_t i = 0; i < _d->pieces.size(); ++i)
	{
		_d->pieces[i]->MoveTo(startSquares[i]);
	}
}

const Point& PieceGroup::get_StartPoint() const
{
	return _d->startPoint;
}

void PieceGroup::set_Pieces( const std::vector<Piece*>& pieces )
{
	_d->pieces = pieces;
}

