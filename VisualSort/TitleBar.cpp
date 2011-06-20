#include "TitleBar.h"

TitleBar::TitleBar()
{
	InitializeComponent();
}

TitleBar::~TitleBar()
{
}

void TitleBar::InitializeComponent()
{
	MouseDown += MouseEventHandler(this, &TitleBar::TitleBar_OnMouseDown);
	MouseMove += MouseEventHandler(this, &TitleBar::TitleBar_OnMouseMove);
	MouseUp	+= MouseEventHandler(this, &TitleBar::TitleBar_OnMouseUp);
	Paint += PaintEventHandler(this, &TitleBar::TitleBar_OnPaint);
	Leave += EventHandler<>(this, &TitleBar::TitleBar_OnLeave);
}

void TitleBar::TitleBar_OnMouseDown( void* sender, MouseEventArgs* e )
{
	moving_ = true;
	down_loc_ = e->Location;
}

void TitleBar::TitleBar_OnMouseMove( void* sender, MouseEventArgs* e )
{
	if (moving_)
	{
		Point loc = get_Parent()->get_Location();
		loc.X += e->Location.X - down_loc_.X;
		loc.Y += e->Location.Y - down_loc_.Y;
		get_Parent()->set_Location(loc);
	}
}

void TitleBar::TitleBar_OnMouseUp( void* sender, MouseEventArgs* e )
{
	moving_ = false;
}

void TitleBar::TitleBar_OnLeave( void* sender, EventArgs* e )
{
	moving_ = false;
}

void TitleBar::TitleBar_OnPaint( void* sender, PaintEventArgs* e )
{
	Brush brush(Color::Silver);
	e->Graphics.FillRectangle(brush, get_ClientRectangle());
}
