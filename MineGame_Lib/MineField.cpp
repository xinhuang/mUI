#include "MineField.h"

#include <mUI.h>
using mUI::System::ArgumentException;

#include "MGame.h"
#include "BlankSquare.h"
#include "SquareFactory.h"

MineField::MineField(MGame* game)
	: _game(game)
	, _squareFactory(NULL)
{
	set_SquareFactory(new SquareFactory());
}

MineField::~MineField()
{
	ClearFields();


	delete _squareFactory;
	_squareFactory = NULL;
}

const Size& MineField::get_Size() const
{
	return _game->get_MineFieldSize();
}

int MineField::get_MineTotal() const
{
	return _game->get_MineTotal();
}

ISquare* MineField::SquareAt(int row, int column)
{
	return _squares.at(row * get_Size().Width + column);
}

SquareFactory* MineField::get_SquareFactory()
{
	return _squareFactory;
}

void MineField::set_SquareFactory( SquareFactory* squareFactory )
{
	_squareFactory = squareFactory;
}

void MineField::Refresh()
{
	ClearFields();
	_squares = _squareFactory->CreateSquares(_game, this);
}

int MineField::get_RowFromIndex( int i )
{
	return get_RowFromIndex(get_Size(), i);
}

int MineField::get_RowFromIndex( const Size& size, int i )
{
	if (i >= get_IndexMax(size) || i < 0)
		throw ArgumentException();
	return i / size.Width;
}

int MineField::get_ColumnFromIndex( int i ) const
{
	return get_ColumnFromIndex(get_Size(), i);
}

int MineField::get_ColumnFromIndex( const Size& size, int i )
{
	if (i >= get_IndexMax(size) || i < 0)
		throw ArgumentException();
	return i % size.Width;
}

int MineField::get_IndexMax() const
{
	return get_IndexMax(get_Size());
}

int MineField::get_IndexMax( const Size& size )
{
	return size.Width * size.Height;
}

int MineField::get_Index( int row, int column ) const
{
	return get_Index(get_Size(), row, column);
}

int MineField::get_Index( const Size& size, int row, int column )
{
	if (row >= size.Height || row < 0 
		|| column >= size.Width || column < 0)
		throw ArgumentException();
	return row * size.Width + column;
}

void MineField::ClearFields()
{
	for (size_t i = 0; i < _squares.size(); ++i)
		delete _squares[i];
	_squares.clear();
}
