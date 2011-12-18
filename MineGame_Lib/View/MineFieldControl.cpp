#include "MineFieldControl.h"

#include "SquareControl.h"

struct MineFieldControl::Data
{
	vector<ISquareView*> squareViews;

	~Data()
	{
		while (!squareViews.empty())
		{
			delete squareViews.back();
			squareViews.pop_back();
		}
	}
};

MineFieldControl::MineFieldControl()
{
	_d = new Data();
}

MineFieldControl::~MineFieldControl()
{
	delete _d;
}

void MineFieldControl::CreateSquares( int squareTotal )
{
	while (squareTotal < _d->squareViews.size())
	{
		delete _d->squareViews.back();
		_d->squareViews.pop_back();
	}

	while (squareTotal < _d->squareViews.size())
	{
		SquareControl* square = new SquareControl();
		_d->squareViews.push_back(square);
		Controls.Add(*square);
	}
}

vector<ISquareView*> MineFieldControl::get_SquareViews() const
{
	return _d->squareViews;
}
