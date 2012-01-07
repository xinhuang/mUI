#include "MGameView.h"

#include "../Presenter/MGame.h"
#include "SquareView.h"
#include "MineFieldView.h"
#include "NumberLabel.h"

using namespace mUI::System::Drawing;

struct MGameView::Data
{
	~Data()
	{
		delete game;
	}

	MGame* game;
	Button gameButton;
	MineFieldView fieldView;
	NumberLabel remainMines;
	bool lost;
};

MGameView::MGameView() : _d(new Data())
{
    _d->game = new MGame(this);

	InitializeComponents();

	FieldSizeChangedEventArgs e(Size(10, 10));
	OnFieldSizeChanged(&e);
	MineTotalChangedEventArgs mineTotalChanged(20);
	OnMineTotalChanged(&mineTotalChanged);
	OnNewGame(&EventArgs::Empty);
}

MGameView::~MGameView()
{
	delete _d;
}

void MGameView::set_RemainMineTotal( int remainingTotal )
{
	_d->remainMines.set_Value(remainingTotal);
}

void MGameView::OnNewGame( EventArgs* e )
{
    NewGame(this, e);
}

void MGameView::OnFieldSizeChanged( FieldSizeChangedEventArgs* e )
{
    FieldSizeChanged(this, e);
}

void MGameView::OnMineTotalChanged( MineTotalChangedEventArgs* e )
{
    MineTotalChanged(this, e);
}

vector<ISquareView*> MGameView::CreateSquares( const Size& fieldSize )
{
	_d->fieldView.Initialize(fieldSize);
	this->Resize(fieldSize)
		.Center();
	return _d->fieldView.get_SquareViews();
}

MGameView& MGameView::Resize( const Size& fieldSize )
{
	Size newSize = _d->fieldView.get_Size();
	newSize.Height += 24 + 10;
	_d->fieldView.set_Location(Point(0, 34));
	set_Size(newSize);
	_d->gameButton.set_Location(
		Point((newSize.Width - _d->gameButton.get_Size().Width) / 2, 
		5));
	return *this;
}

MGameView& MGameView::Center()
{
	int x = (Application::get_Size().Width - get_Size().Width) / 2;
	int y = (Application::get_Size().Height - get_Size().Height) / 2;
	set_Location(Point(x, y));

	return *this;
}

void MGameView::OnSquareUncovered( void* sender, SquareEventArgs* e )
{
	SquareUncovered(this, e);
}

void MGameView::OnSquareToggleFlag( void* sender, SquareEventArgs* e )
{
	SquareToggleFlag(this, e);
}

void MGameView::InitializeComponents()
{
	SuspendLayout();

    set_Text(L"Mine Game v0.1");

	Controls.Add(_d->gameButton);
    _d->gameButton.set_NormalImage(L"res/smile.png");
	_d->gameButton.set_PressedImage(L"res/smile_pressed.png");
	_d->gameButton.set_Size(Size(24, 24));
	_d->gameButton.Show();
	_d->gameButton.Click += EventHandler<>(this, &MGameView::OnGameButtonClicked);

	Controls.Add(_d->fieldView);
	_d->fieldView.Uncover += SquareEventHandler(this, &MGameView::OnSquareUncovered);
	_d->fieldView.ToggleFlag += SquareEventHandler(this, &MGameView::OnSquareToggleFlag);
	_d->fieldView.SquareMouseDown += MouseEventHandler(this, &MGameView::OnSquareMouseDown);
	_d->fieldView.SquareMouseUp += MouseEventHandler(this, &MGameView::OnSquareMouseUp);
	_d->fieldView.Show();

	Controls.Add(_d->remainMines);
	_d->remainMines.set_Location(Point(5, 5));
	_d->remainMines.set_Size(Size(39, 24));
	_d->remainMines.set_AnchorStyles(AnchorStyles::TopLeft);
	_d->remainMines.Show();

	ResumeLayout(true);
}

void MGameView::OnGameButtonClicked(void* sender, EventArgs* e)
{
	OnNewGame(&EventArgs::Empty);
}

void MGameView::OnSquareMouseDown( void* sender, MouseEventArgs* e )
{
    if (_d->lost)
        return;
	if (e->Button == MouseButtons::Left)
	{
		_d->gameButton.set_NormalImage(L"res/oops.png");
	}
}

void MGameView::OnSquareMouseUp( void* sender, MouseEventArgs* e )
{
    if (_d->lost)
        return;
	if (e->Button == MouseButtons::Left)
	{
		_d->gameButton.set_NormalImage(L"res/smile.png");
	}
}

void MGameView::set_Lost( bool value )
{
    _d->lost = value;
    if (_d->lost)
    {
        _d->gameButton.set_NormalImage(L"res/xxface.png");
    }
    else
    {
        _d->gameButton.set_NormalImage(L"res/smile.png");
    }
}
