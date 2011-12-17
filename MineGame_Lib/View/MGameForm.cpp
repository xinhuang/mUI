#include "MGameForm.h"

#include "../Presenter/MGame.h"
#include "SquareControl.h"

using namespace mUI::System::Drawing;

struct MGameForm::Data
{
	vector<ISquareView*> squareStates;
	MGame* game;
	Button gameButton;
};

MGameForm::MGameForm() : _data(new Data())
{
    _data->game = new MGame(this);

	InitializeComponents();

	FieldSizeChangedEventArgs e(Size(10, 10));
	OnFieldSizeChanged(&e);
	MineTotalChangedEventArgs mineTotalChanged(20);
	OnMineTotalChanged(&mineTotalChanged);
	OnNewGame(&EventArgs::Empty);
}

MGameForm::~MGameForm()
{
	delete _data->game;
	DisposeSquares();
	delete _data;
}

void MGameForm::set_RemainingMineTotal( int remainingTotal )
{

}

void MGameForm::OnNewGame( EventArgs* e )
{
    NewGame(this, e);
}

void MGameForm::OnFieldSizeChanged( FieldSizeChangedEventArgs* e )
{
    FieldSizeChanged(this, e);
}

void MGameForm::OnMineTotalChanged( MineTotalChangedEventArgs* e )
{
    MineTotalChanged(this, e);
}

void MGameForm::DisposeSquares()
{
    for (vector<ISquareView*>::const_iterator iter = _data->squareStates.begin();
        iter != _data->squareStates.end(); ++iter)
    {
        delete *iter;
    }
    _data->squareStates.clear();
}

vector<ISquareView*> MGameForm::CreateSquares( const Size& fieldSize )
{
	DisposeSquares();
	this->Resize(fieldSize)
		.Center();

	Point squareUpperLeft(0, 35);

	for (int y = 0; y < fieldSize.Height; ++y)
	{
		for (int x = 0; x < fieldSize.Width; ++x)
		{
			SquareControl* square = new SquareControl(this, x, y);
			_data->squareStates.push_back(square);
			Controls.Add(*square);
			square->set_Location(Point(x * SquareControl::get_ImageSize().Width, 
				y * SquareControl::get_ImageSize().Height)  + squareUpperLeft);
			square->Show();
		}
    }
	return _data->squareStates;
}

MGameForm& MGameForm::Resize( const Size& fieldSize )
{
	Size newSize = fieldSize * SquareControl::get_ImageSize();
	newSize.Height += 24 + 10;
	set_Size(newSize);
	_data->gameButton.set_Location(
		Point((newSize.Width - _data->gameButton.get_Size().Width) / 2, 
		5));
	return *this;
}

MGameForm& MGameForm::Center()
{
	int x = (Application::get_Size().Width - get_Size().Width) / 2;
	int y = (Application::get_Size().Height - get_Size().Height) / 2;
	set_Location(Point(x, y));

	return *this;
}

void MGameForm::OnSquareUncovered( SquareEventArgs* e )
{
	SquareUncovered(this, e);
}

void MGameForm::Uncover( ISquareView* squareView )
{
	SquareEventArgs e(squareView);
	OnSquareUncovered(&e);
}

void MGameForm::ToggleFlag( ISquareView* squareView )
{
	SquareEventArgs e(squareView);
	OnSquareToggleFlag(&e);
}

void MGameForm::OnSquareToggleFlag( SquareEventArgs* e )
{
	SquareToggleFlag(this, e);
}

void MGameForm::InitializeComponents()
{
	set_Text(L"Mine Game v0.1");
	_data->gameButton.set_NormalImage(L"res/smile.png");
	_data->gameButton.set_PressedImage(L"res/smile_pressed.png");
	_data->gameButton.set_Size(Size(24, 24));
	_data->gameButton.Show();
	_data->gameButton.Click += EventHandler<>(this, &MGameForm::OnGameButtonClicked);
	Controls.Add(_data->gameButton);
}

void MGameForm::OnGameButtonClicked(void* sender, EventArgs* e)
{
	OnNewGame(&EventArgs::Empty);
}
