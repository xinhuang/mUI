#include "MGameForm.h"

using namespace mUI::System::Drawing;

MGameForm::MGameForm()
{
	set_Text(L"Mine Game v0.1");
}

void MGameForm::set_SquareState( const Point& location, SquareState::Enum state )
{

}

void MGameForm::set_RemainingMineTotal( int remainingTotal )
{

}

void MGameForm::OnPaint( PaintEventArgs* e )
{
	Graphics& g = e->Graphics;

	SolidBrush normal_brush(SystemColors::Control);
	SolidBrush highlight_brush(Color::Silver);
	SolidBrush dark_brush(Color::Grey);

	Rectangle rect = get_ClientRectangle();
	e->Graphics.FillRectangle(dark_brush, rect);
}
