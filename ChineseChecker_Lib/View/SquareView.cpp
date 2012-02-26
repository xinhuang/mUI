#include "SquareView.h"

SquareView::SquareView()
{
    InitializeComponents();
}

void SquareView::InitializeComponents()
{
    set_BackColor(Color::Transparent);
    set_Size(Size(Width, Height));
}

void SquareView::OnPaint( PaintEventArgs* e )
{
    Control::OnPaint(e);
    e->Graphics.FillEllipse(SolidBrush(Color::Grey), 0, 0, Width, Height);
}

