#include "MGameForm.h"

#include "../Presenter/MGame.h"
#include "SquareControl.h"

using namespace mUI::System::Drawing;

MGameForm::MGameForm()
{
	set_Text(L"Mine Game v0.1");
    _game = new MGame(this);
}

void MGameForm::set_SquareState( const Point& location, SquareState::Enum state, IntPtr param )
{

}

void MGameForm::set_RemainingMineTotal( int remainingTotal )
{

}

void MGameForm::OnPaint( PaintEventArgs* e )
{
	Graphics& g = e->Graphics;

	SolidBrush bgBrush(SystemColors::Control);

	Rectangle rect = get_ClientRectangle();
	e->Graphics.FillRectangle(bgBrush, rect);
}

void MGameForm::OnNewGame( void* sender, EventArgs* e )
{
    NewGame(this, e);
}

void MGameForm::OnFieldSizeChanged( void* sender, FieldSizeChangedEventArgs* e )
{
    FieldSizeChanged(this, e);
}

void MGameForm::OnMineTotalChanged( void* sender, MineTotalChangedEventArgs* e )
{
    MineTotalChanged(this, e);
}

void MGameForm::DisposeSquares()
{
    for (vector<SquareControl*>::const_iterator iter = _squareStates.begin();
        iter != _squareStates.end(); ++iter)
    {
        delete *iter;
    }
    _squareStates.clear();
}

MGameForm::~MGameForm()
{
    DisposeSquares();
}

void MGameForm::CreateSquares( const Size& size )
{
    size_t total = size.Width * size.Height;
    for (size_t i = 0; i < total; ++i)
    {
        _squareStates.push_back(new SquareControl());
        Controls.Add(*_squareStates[i]);
    }
}
