#include "Button.h"

#include "../Drawing/Drawing.h"

using namespace mUI::System::Drawing;

namespace mUI{ namespace System{  namespace Forms{

Button::Button()
{
	normal_color_ = Color::Black;
	pressed_color_ = Color::Silver;
	state_ = Normal;
}

void Button::OnMouseUp( MouseEventArgs* e )
{
	Control::OnMouseUp(e);

	if (Drawing::Rectangle(Point::Empty, get_Size()).Contains(e->Location))
	{
		if (state_ & Pressed)
		{
			OnClick(&EventArgs::Empty);
		}
		state_ = Hover;
	}
	else
	{
		state_ = Normal;
	}
}

void Button::OnMouseHover( EventArgs* e )
{
	Control::OnMouseHover(e);
	state_ = static_cast<State>(state_ | Hover);
}

void Button::OnMouseLeave( EventArgs* e )
{
	Control::OnMouseLeave(e);
	state_ = static_cast<State>(state_ & ~Hover);
}

void Button::OnMouseDown( MouseEventArgs* e )
{
	Control::OnMouseDown(e);
	state_ = static_cast<State>(state_ | Pressed);
}

void Button::OnMouseEnter( EventArgs* e )
{
	Control::OnMouseEnter(e);
	state_ = static_cast<State>(state_ | Hover);
}

void Button::OnPaint( PaintEventArgs* e )
{
	if (state_ == Normal)
		set_BackColor(SystemColors::ButtonFace);
	else if (state_ == HoverPressed)
		set_BackColor(SystemColors::ButtonShadow);
	else
		set_BackColor(SystemColors::ButtonHighlight);

	ButtonBase::OnPaint(e);

	Graphics& g = e->Graphics;

	Drawing::Pen pen(Color::Black);
	g.DrawRectangle(pen, 1, 1, get_Size().Width - 1, get_Size().Height - 1);

	Brush brush(SystemColors::ControlText);
	g.DrawString(get_Text(), *SystemFonts::DefaultFont, brush, PointF(3, 3));
}

void Button::OnMouseMove( MouseEventArgs* e )
{
	Control::OnMouseMove(e);

	if (!Drawing::Rectangle(Point::Empty, get_Size()).Contains(e->Location))
	{
		state_ = static_cast<State>(state_ & ~Hover);
	}
	else
	{
		state_ = static_cast<State>(state_ | Hover);
	}
}

void Button::OnLeave( EventArgs* e )
{
	state_ = Normal;
}

}}}
