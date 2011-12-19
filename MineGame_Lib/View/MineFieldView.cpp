#include "MineFieldView.h"

#include "SquareView.h"
#include "MGameView.h"

struct MineFieldView::Data
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

MineFieldView::MineFieldView()
{
	_d = new Data();
}

MineFieldView::~MineFieldView()
{
	delete _d;
}

void MineFieldView::CreateSquares(const Size& fieldSize)
{
	size_t squareTotal = fieldSize.Width * fieldSize.Height;
	while (squareTotal < _d->squareViews.size())
	{
		delete _d->squareViews.back();
		_d->squareViews.pop_back();
	}

	while (squareTotal > _d->squareViews.size())
	{
		SquareView* square = new SquareView();
		_d->squareViews.push_back(square);
		Controls.Add(*square);
	}

	Resize(fieldSize);
}

vector<ISquareView*> MineFieldView::get_SquareViews() const
{
	return _d->squareViews;
}

void MineFieldView::Resize(const Size& fieldSize)
{
	Size newSize = fieldSize * SquareView::get_ImageSize();
	set_Size(newSize);
}

void MineFieldView::Uncover( ISquareView* squareView )
{
	MGameView* parent = static_cast<MGameView*>(get_Parent());
	parent->Uncover(squareView);
}

void MineFieldView::ToggleFlag( ISquareView* squareView )
{
	MGameView* parent = static_cast<MGameView*>(get_Parent());
	parent->ToggleFlag(squareView);
}
