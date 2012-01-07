#include "MGame.h"
#include "MineField.h"
#include "ISquare.h"

#include <mUI.h>
#include "../View/View.h"

struct MGame::Data
{
	Data()
		: flagCount(0)
	{
	}
	~Data()
	{
		delete mineField;
	}

    MineField* mineField;
    View* view;
    bool lost;
	int flagCount;
};

MGame::MGame(View* view)
	: _d(new Data())
{
    _d->view = view;
    set_Lost(false);
    _d->mineField = new MineField(this);
    _d->view->FieldSizeChanged += EventHandler<FieldSizeChangedEventArgs*>(this, &MGame::OnFieldSizeChanged);
    _d->view->MineTotalChanged += EventHandler<MineTotalChangedEventArgs*>(this, &MGame::OnMineTotalChanged);
    _d->view->NewGame += EventHandler<>(this, &MGame::OnNewGame);
	_d->view->SquareUncovered += SquareEventHandler(this, &MGame::OnSquareUncovered);
	_d->view->SquareToggleFlag += SquareEventHandler(this, &MGame::OnSquareToggleFlag);
}

MGame::~MGame()
{
	delete _d;
}

const Size& MGame::get_MineFieldSize() const
{
	return _d->mineField->get_Size();
}

void MGame::set_MineFieldWidth(int width)
{
	_d->mineField->set_Width(width);
}

void MGame::set_MineFieldHeight(int height)
{
	_d->mineField->set_Height(height);
}

void MGame::set_MineTotal(int mineTotal)
{
	_d->mineField->set_MineTotal(mineTotal);
}

int MGame::get_MineTotal() const
{
	return _d->mineField->get_MineTotal();
}
	
void MGame::NewGame()
{
	_d->flagCount = 0;
	set_Lost(false);
    _d->mineField->Refresh();
    vector<ISquareView*> squareViews = _d->view->CreateSquares(_d->mineField->get_Size());
	for (int i = 0; i < _d->mineField->get_IndexMax(); ++i)
	{
		ISquare* square = _d->mineField->SquareAt(i);
		ISquareView* view = squareViews[i];
		square->Bind(view);
	}
}

void MGame::Uncover(int x, int y)
{
}

void MGame::Lose()
{
	if (_d->lost)
		return;

    set_Lost(true);
	for (int i = 0; i < _d->mineField->get_IndexMax(); ++i)
	{
		ISquare* square = _d->mineField->SquareAt(i);
		if (square->get_State() == SquareState::Covered)
			square->Uncover();
	}
}

MineField* MGame::get_MineField()
{
	return _d->mineField;
}

void MGame::OnNewGame( void* sender, EventArgs* e )
{
    NewGame();
}

void MGame::OnFieldSizeChanged( void* sender, FieldSizeChangedEventArgs* e )
{
    set_MineFieldHeight(e->get_Size().Height);
    set_MineFieldWidth(e->get_Size().Width);
}

void MGame::OnMineTotalChanged( void* sender, MineTotalChangedEventArgs* e )
{
    set_MineTotal(e->get_MineTotal());
}

void MGame::OnSquareUncovered( void* sender, SquareEventArgs* e )
{
	ISquareView* squareView = e->get_SquareView();
	const Point& location = squareView->get_Coordinates();
	ISquare* square = _d->mineField->SquareAt(location);
	square->Uncover();
}

bool MGame::IsLost() const
{
	return _d->lost;
}

void MGame::OnSquareToggleFlag( void* sender, SquareEventArgs* e )
{
	ISquareView* squareView = e->get_SquareView();
	const Point& location = squareView->get_Coordinates();
	ISquare* square = _d->mineField->SquareAt(location);
	square->ToggleFlag();
}

void MGame::set_Lost( bool value )
{
    _d->lost = value;
    _d->view->set_Lost(_d->lost);
}

void MGame::DecFlagCount()
{
	--_d->flagCount;
	UpdateRemainMineTotalToView();
}

void MGame::IncFlagCount()
{
	++_d->flagCount;
	UpdateRemainMineTotalToView();
}

int MGame::get_FlagCount() const
{
	return _d->flagCount;
}

void MGame::UpdateRemainMineTotalToView()
{
	_d->view->set_RemainMineTotal(_d->mineField->get_MineTotal() - _d->flagCount);
}
