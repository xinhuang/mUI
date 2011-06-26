#include "Button.h"

#include "../Drawing/Drawing.h"

using namespace mUI::System::Drawing;

namespace mUI{ namespace System{  namespace Forms{

Button::Button()
{
	normal_color_ = Color::Black;
	pressed_color_ = Color::Silver;
	state_ = Normal;
	for (size_t i = 0; i < StateMax; ++i)
	{
		state_images_[i] = NULL;
	}
}

void Button::OnMouseUp( MouseEventArgs* e )
{
	Control::OnMouseUp(e);
	if (e->Button != MouseButtons::Left)
		return;

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
	if (e->Button == MouseButtons::Left)
		state_ = static_cast<State>(state_ | Pressed);
}

void Button::OnMouseEnter( EventArgs* e )
{
	Control::OnMouseEnter(e);
	state_ = static_cast<State>(state_ | Hover);
}

void Button::OnPaint( PaintEventArgs* e )
{
	if (state_ == Hover)
	{
		set_BackColor(SystemColors::ButtonHighlight);
		Image* image = state_images_[Hover];
		if (image == NULL)
			image = state_images_[Normal];
		set_BackgroundImage(image, false);
	}	
	else if (state_ == HoverPressed)
	{
		set_BackColor(SystemColors::ButtonShadow);
		Image* image = state_images_[Pressed];
		if (image == NULL)
			image = state_images_[Normal];
		set_BackgroundImage(image, false);
	}
	else
	{
		set_BackColor(SystemColors::ButtonFace);
		set_BackgroundImage(state_images_[Normal], false);
	}

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

void Button::set_NormalImage( const String& image )
{
	set_StateImage(Normal, image);
}

void Button::set_HoverImage( const String& image )
{
	set_StateImage(Hover, image);
}

void Button::set_PressedImage( const String& image )
{
	set_StateImage(Pressed, image);
}

void Button::set_StateImage( State s, const String& image )
{
	if (state_images_[s] != NULL)
	{
		delete state_images_[s];
	}
	state_images_[s] = Image::FromFile(image);
}

Button::~Button()
{
	set_BackgroundImage(NULL, false);
	for (size_t i = 0; i < StateMax; ++i)
	{
		delete state_images_[i];
		state_images_[i] = NULL;
	}
}

}}}
