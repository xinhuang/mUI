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
		square->MouseClick += MouseEventHandler(this, &MineFieldView::OnSquareMouseClick);
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

void MineFieldView::OnUncover( SquareEventArgs* e )
{
	Uncover(this, e);
}

void MineFieldView::OnToggleFlag( SquareEventArgs* e )
{
	ToggleFlag(this, e);
}

void MineFieldView::OnSquareMouseClick( void* sender, MouseEventArgs* e )
{
	SquareView* square = static_cast<SquareView*>(sender);
	SquareEventArgs sea(square);
	switch (e->Button)
	{
	case MouseButtons::Left:
		OnUncover(&sea);
		break;

	case MouseButtons::Right:
		OnToggleFlag(&sea);
		break;
	}
}
