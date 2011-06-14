#include "TitleBar.h"

#include "../Drawing/Size.h"
#include "../Drawing/Pen.h"
#include "../Drawing/Graphics.h"
using namespace mUI::System::Drawing;

#include "SystemInformation.h"

namespace mUI{ namespace System{  namespace Forms{

Form::TitleBar::TitleBar(Form& form)
{
	form.Deactivate += EventHandler<EventArgs>(this, &TitleBar::Form_OnDeactivate);
	form.SizeChanged += EventHandler<EventArgs>(this, &TitleBar::Form_OnSizeChanged);
	SetSize(Size(form.GetSize().Width, SystemInformation::GetCaptionHeight()));
	SetText(form.GetText());

	InitializeComponent();
}

Form::TitleBar::~TitleBar()
{
}

void Form::TitleBar::InitializeComponent()
{
	SetLocation(Point(0, 0));
	close_.SetLocation(Point(GetSize().Width - BUTTON_WIDTH - 4, 
		(TITLE_BAR_HEIGHT - BUTTON_HEIGHT) / 2));
	close_.SetSize(Size(BUTTON_WIDTH, BUTTON_HEIGHT));
	close_.Clicked += EventHandler<EventArgs>(this, &TitleBar::TitleBar_OnCloseClick);
	Controls.Add(close_);

	SetBackColor(Color::Silver);
	Paint += PaintEventHandler(this, &TitleBar::TitleBar_OnPaint);
	MouseDown += MouseEventHandler(this, &TitleBar::TitleBar_OnMouseDown);
	MouseUp += MouseEventHandler(this, &TitleBar::TitleBar_OnMouseUp);
	MouseMove += MouseEventHandler(this, &TitleBar::TitleBar_OnMouseMove);
}

void Form::TitleBar::TitleBar_OnCloseClick( void* sender, EventArgs e )
{
	Form* form = reinterpret_cast<Form*>(GetParent());
	assert(form != NULL);
	form->Close();
}

void Form::TitleBar::StartMoving( const Point& pt )
{
	moving_ = true;
	prev_pt_ = pt;
}

void Form::TitleBar::Moving( const Point& pt )
{
	if (moving_)
	{
		Point loc = GetLocation() + GetParent()->GetLocation();
		loc.X += pt.X - prev_pt_.X;
		loc.Y += pt.Y - prev_pt_.Y;
		GetParent()->SetLocation(loc);
	}
}

void Form::TitleBar::StopMoving()
{
	moving_ = false;
}

void Form::TitleBar::TitleBar_OnMouseDown( void* sender, MouseEventArgs e )
{
	StartMoving(e.Location);
}

void Form::TitleBar::TitleBar_OnMouseUp( void* sender, MouseEventArgs e )
{
	StopMoving();
}

void Form::TitleBar::Form_OnDeactivate( void* sender, EventArgs e )
{
	StopMoving();
}

void Form::TitleBar::Form_OnSizeChanged( void* sender, EventArgs e )
{
	Form* form = reinterpret_cast<Form*>(sender);
	SetSize(Size(form->GetSize().Width, 24));
	close_.SetLocation(Point(GetSize().Width - BUTTON_WIDTH - 4, 
		(TITLE_BAR_HEIGHT - BUTTON_HEIGHT) / 2));
}

void Form::TitleBar::TitleBar_OnPaint( void* sender, PaintEventArgs e )
{
	Graphics& g = e.Graphics;
	Pen pen(Color::Black);
	g.DrawRectangle(pen, 1, 1, GetSize().Width - 1, GetSize().Height - 1);
}

void Form::TitleBar::TitleBar_OnMouseMove( void* sender, MouseEventArgs e )
{
	Moving(e.Location);
}

}}}
