#include "MGameForm.h"

#include "../Presenter/MGame.h"
#include "SquareControl.h"

using namespace mUI::System::Drawing;

MGameForm::MGameForm()
{
	set_Text(L"Mine Game v0.1");
    _game = new MGame(this);

    FieldSizeChangedEventArgs e(Size(16, 16));
    OnFieldSizeChanged(&e);
    OnNewGame(&EventArgs::Empty);
}

void MGameForm::set_SquareState( const Point& location, SquareState::Enum state, IntPtr param )
{

}

void MGameForm::set_RemainingMineTotal( int remainingTotal )
{

}

void MGameForm::OnPaint( PaintEventArgs* e )
{
    Form::OnPaint(e);
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
    for (int x = 0; x < size.Width; ++x)
    {
        for (int y = 0; y < size.Height; ++y)
        {
            SquareControl* square = new SquareControl();
            _squareStates.push_back(square);
            Controls.Add(*square);
            square->set_Location(Point(x * square->get_Size().Width, y * square->get_Size().Height));
            square->Show();
        }
    }
}
