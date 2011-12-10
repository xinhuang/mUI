#include "MGameForm.h"

#include "../Presenter/MGame.h"

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
