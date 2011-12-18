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
	return _size;
}

int MineField::get_MineTotal() const
{
	return _mineTotal;
}

ISquare* MineField::SquareAt(int x, int y)
{
	return _squares.at(y * get_Size().Width + x);
}

ISquare* MineField::SquareAt(const Point& location)
{
	return SquareAt(location.X, location.Y);
}

ISquare* MineField::SquareAt( size_t i )
{
	int x = get_XFromIndex(i);
	int y = get_YFromIndex(i);
	return SquareAt(x, y);
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

int MineField::get_YFromIndex( int i )
{
	return get_YFromIndex(get_Size(), i);
}

int MineField::get_YFromIndex( const Size& size, int i )
{
	if (i >= get_IndexMax(size) || i < 0)
		throw ArgumentException();
	return i / size.Width;
}

int MineField::get_XFromIndex( int i ) const
{
	return get_XFromIndex(get_Size(), i);
}

int MineField::get_XFromIndex( const Size& size, int i )
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

int MineField::get_Index( int x, int y ) const
{
	return get_Index(get_Size(), x, y);
}

int MineField::get_Index( const Size& size, int x, int y )
{
	if (x >= 0 && x < size.Width && y >= 0 && y < size.Height)
		return y * size.Width + x;
	return -1;
}

int MineField::get_Index( const Point& location ) const
{
	return get_Index(location.X, location.Y);
}

void MineField::ClearFields()
{
	for (size_t i = 0; i < _squares.size(); ++i)
		delete _squares[i];
	_squares.clear();
}

void MineField::set_Size( const Size& size )
{
	_size = size;
}

void MineField::set_Width( int width )
{
	_size.Width = width;
}

void MineField::set_Height( int height )
{
	_size.Height = height;
}

void MineField::set_MineTotal( int mineTotal )
{
	_mineTotal = mineTotal;
}

bool MineField::IsMineAt( int i ) const
{
	if (i < 0 || static_cast<size_t>(i) >= _squares.size())
		return false;
	return _squares[i]->HasMine();
}

bool MineField::IsMineAt( int x, int y ) const
{
	return IsMineAt(get_Index(x, y));
}

int MineField::get_AdjacentMineTotal( const Point& location ) const
{
	int n = 0;
	int x = location.X, y = location.Y;

	n += IsMineAt(x - 1, y - 1) ? 1 : 0;
	n += IsMineAt(x - 1, y) ? 1 : 0;
	n += IsMineAt(x - 1, y + 1) ? 1 : 0;

	n += IsMineAt(x, y - 1) ? 1 : 0;
	n += IsMineAt(x, y + 1) ? 1 : 0;

	n += IsMineAt(x + 1, y - 1) ? 1 : 0;
	n += IsMineAt(x + 1, y) ? 1 : 0;
	n += IsMineAt(x + 1, y + 1) ? 1 : 0;

	return n;
}

void MineField::UncoverAdjacent( const Point& location )
{
	TryUncover(location.X - 1, location.Y - 1);
	TryUncover(location.X - 1, location.Y);
	TryUncover(location.X - 1, location.Y + 1);

	TryUncover(location.X, location.Y - 1);
	TryUncover(location.X, location.Y + 1);

	TryUncover(location.X + 1, location.Y - 1);
	TryUncover(location.X + 1, location.Y);
	TryUncover(location.X + 1, location.Y + 1);
}

void MineField::TryUncover( int x, int y )
{
	if (x < 0 || x >= get_Size().Width || y < 0 || y >= get_Size().Height)
		return;
	if (SquareAt(x, y)->get_State() == SquareState::Covered)
		SquareAt(x, y)->Uncover();
}

vector<vector<bool>> MineField::GenerateFieldMap( const Size& fieldSize, int mineTotal ) const
{
    vector<vector<bool>> fieldMap(fieldSize.Width, vector<bool>(1));

    return fieldMap;
}
