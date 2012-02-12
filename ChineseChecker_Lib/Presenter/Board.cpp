#include "Board.h"
#include "Square.h"

#include <mUI.h>
using namespace mUI::System;
using namespace mUI::System::Drawing;

struct Board::Data
{
	Data() 
		: goalSquares_0_4(15, nullptr) 
		, goalSquares_4_0(15, nullptr) 
		, goalSquares_12_4(15, nullptr)
		, goalSquares_16_12(15, nullptr)
		, goalSquares_12_16(15, nullptr)
		, goalSquares_4_12(15, nullptr)
		, squares(Width * Height, nullptr)
	{
	}

	vector<Square*> goalSquares_0_4;
	vector<Square*> goalSquares_4_0;
	vector<Square*> goalSquares_12_4;
	vector<Square*> goalSquares_16_12;
	vector<Square*> goalSquares_12_16;
	vector<Square*> goalSquares_4_12;
	vector<Square*> squares;
};

Board::Board() : _d(new Data())
{
	for (int x = 0; x < Width; ++x)
	{
		for (int y = 0; y < Height; ++y)
		{
			_d->squares[GetSquareIndex(x, y)] = new Square(Point(x, y));
		}
	}

	InitializeGoalSquares();
}

Board::~Board()
{
	for (auto iter = _d->squares.begin(); iter != _d->squares.end(); ++iter)
		delete *iter;
	_d->squares.clear();
	delete _d;
}

vector<Square*> Board::GetGoalSquares( const Point& goalLocation ) const
{
	if (goalLocation == Point(0, 4))
		return _d->goalSquares_0_4;
	else if (goalLocation == Point(4, 0))
		return _d->goalSquares_4_0;
	else if (goalLocation == Point(12, 4))
		return _d->goalSquares_12_4;
	else if (goalLocation == Point(16, 12))
		return _d->goalSquares_16_12;
	else if (goalLocation == Point(12, 16))
		return _d->goalSquares_12_16;
	else if (goalLocation == Point(4, 12))
		return _d->goalSquares_4_12;
	throw new ArgumentException();
}

Square* Board::SquareAt( const Point& location )
{
	return _d->squares[GetSquareIndex(location)];
}

int Board::GetSquareIndex(const Point& location) const
{
	return GetSquareIndex(location.X, location.Y);
}

int Board::GetSquareIndex(int x, int y) const
{
	return y * Width + x;
}

void Board::InitializeGoalSquares()
{
	int i = 0;
	for (int y = 4; y < 9; ++y)
	{
		for (int x = y - 4; x < 5; ++x)
		{
			_d->goalSquares_0_4[i++] = SquareAt(Point(x, y));
		}
	}

	i = 0;
	for (int y = 4; y < 9; ++y)
	{
		for (int x = y + 4; x < 13; ++x)
		{
			_d->goalSquares_12_4[i++] = SquareAt(Point(x, y));
		}
	}

	i = 0;
	for (int y = 12; y < 17; ++y)
	{
		for (int x = y - 4; x < 13; ++x)
		{
			_d->goalSquares_12_16[i++] = SquareAt(Point(x, y));
		}
	}

	i = 0;
	for (int x = 4; x < 9; ++x)
	{
		for (int y = x - 4; y < 5; ++y)
		{
			_d->goalSquares_4_0[i++] = SquareAt(Point(x, y));
		}
	}

	i = 0;
	for (int x = 12; x < 17; ++x)
	{
		for (int y = x - 4; y < 13; ++y)
		{
			_d->goalSquares_16_12[i++] = SquareAt(Point(x, y));
		}
	}

	i = 0;
	for (int x = 4; x < 9; ++x)
	{
		for (int y = x + 4; y < 13; ++y)
		{
			_d->goalSquares_4_12[i++] = SquareAt(Point(x, y));
		}
	}
}

void Board::Reset()
{

}
