#include "MGameView.h"

#include "../Presenter/MGame.h"
#include "SquareView.h"
#include "MineFieldView.h"

using namespace mUI::System::Drawing;

struct MGameView::Data
{
	MGame* game;
	Button gameButton;
	MineFieldView fieldView;
	bool lost;
};

MGameView::MGameView() : _data(new Data())
{
    _data->game = new MGame(this);

	InitializeComponents();

	FieldSizeChangedEventArgs e(Size(10, 10));
	OnFieldSizeChanged(&e);
	MineTotalChangedEventArgs mineTotalChanged(20);
	OnMineTotalChanged(&mineTotalChanged);
	OnNewGame(&EventArgs::Empty);
}

MGameView::~MGameView()
{
	delete _data->game;
	delete _data;
}

void MGameView::set_RemainingMineTotal( int remainingTotal )
{

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
	_data->fieldView.CreateSquares(fieldSize);
	this->Resize(fieldSize)
		.Center();
	return _data->fieldView.get_SquareViews();
}

MGameView& MGameView::Resize( const Size& fieldSize )
{
	Size newSize = _data->fieldView.get_Size();
	newSize.Height += 24 + 10;
	_data->fieldView.set_Location(Point(0, 34));
	set_Size(newSize);
	_data->gameButton.set_Location(
		Point((newSize.Width - _data->gameButton.get_Size().Width) / 2, 
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
    set_Text(L"Mine Game v0.1");
    _data->gameButton.set_NormalImage(L"res/smile.png");
	_data->gameButton.set_PressedImage(L"res/smile_pressed.png");
	_data->gameButton.set_Size(Size(24, 24));
	_data->gameButton.Show();
	_data->gameButton.Click += EventHandler<>(this, &MGameView::OnGameButtonClicked);
	Controls.Add(_data->gameButton);

	_data->fieldView.Uncover += SquareEventHandler(this, &MGameView::OnSquareUncovered);
	_data->fieldView.ToggleFlag += SquareEventHandler(this, &MGameView::OnSquareToggleFlag);
	_data->fieldView.SquareMouseDown += MouseEventHandler(this, &MGameView::OnSquareMouseDown);
	_data->fieldView.SquareMouseUp += MouseEventHandler(this, &MGameView::OnSquareMouseUp);
	Controls.Add(_data->fieldView);
	_data->fieldView.Show();
}

void MGameView::OnGameButtonClicked(void* sender, EventArgs* e)
{
	OnNewGame(&EventArgs::Empty);
}

void MGameView::OnSquareMouseDown( void* sender, MouseEventArgs* e )
{
    if (_data->lost)
        return;
	if (e->Button == MouseButtons::Left)
	{
		_data->gameButton.set_NormalImage(L"res/oops.png");
	}
}

void MGameView::OnSquareMouseUp( void* sender, MouseEventArgs* e )
{
    if (_data->lost)
        return;
	if (e->Button == MouseButtons::Left)
	{
		_data->gameButton.set_NormalImage(L"res/smile.png");
	}
}

void MGameView::set_Lost( bool value )
{
    _data->lost = value;
    if (_data->lost)
    {
        _data->gameButton.set_NormalImage(L"res/xxface.png");
    }
    else
    {
        _data->gameButton.set_NormalImage(L"res/smile.png");
    }
}
