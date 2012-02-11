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
	{
		int i = 0;
		for (int x = 0; x < 5; ++x)
		{
			for (int y = x + 4; y < 9; ++y)
			{
				goalSquares_0_4[i++] = new Square(Point(x, y));
			}
		}

		i = 0;
		for (int y = 0; y < 5; ++y)
		{
			for (int x = 4; x < 5 + y; ++x)
			{
				goalSquares_4_0[i++] = new Square(Point(x, y));
			}
		}

		i = 0;
		for (int y = 4; y < 9; ++y)
		{
			for (int x = 8 + y - 4; x < 13; ++x)
			{
				goalSquares_12_4[i++] = new Square(Point(x, y));
			}
		}

		i = 0;
		for (int x = 12; x < 17; ++x)
		{
			for (int y = 8 + x - 12; y < 13; ++y)
			{
				goalSquares_16_12[i++] = new Square(Point(x, y));
			}
		}

		i = 0;
		for (int y = 12; y < 17; ++y)
		{
			for (int x = y - 4; x < 13; ++x)
			{
				goalSquares_12_16[i++] = new Square(Point(x, y));
			}
		}
	}
	~Data()
	{
		ClearVector(goalSquares_0_4);
		ClearVector(goalSquares_4_0);
	}
	template <typename T>
	void ClearVector(T& vec) const
	{
		for (auto iter = vec.begin(); iter != vec.end(); ++iter)
			delete *iter;
		vec.clear();
	}

	vector<Square*> goalSquares_0_4;
	vector<Square*> goalSquares_4_0;
	vector<Square*> goalSquares_12_4;
	vector<Square*> goalSquares_16_12;
	vector<Square*> goalSquares_12_16;
};

Board::Board() : _d(new Data())
{
}

Board::~Board()
{
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
	throw new ArgumentException();
}
