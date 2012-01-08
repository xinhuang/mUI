#include "Button.h"

#include <System.Drawing/Drawing.h>

using namespace mUI::System::Drawing;

namespace mUI{ namespace System{  namespace Forms{

Button::Button()
{
	_normalColor = Color::Black;
	_pressedColor = Color::Silver;
	_state = Normal;
	for (size_t i = 0; i < StateMax; ++i)
	{
		_stateImages[i] = null;
	}
}

void Button::OnMouseUp( MouseEventArgs* e )
{
	Control::OnMouseUp(e);
	if (e->Button != MouseButtons::Left)
		return;

	if (Drawing::Rectangle(Point::Empty, get_Size()).Contains(e->Location))
	{
		if (_state & Pressed)
		{
			OnClick(&EventArgs::Empty);
		}
		_state = Hover;
	}
	else
	{
		_state = Normal;
	}
}

void Button::OnMouseHover( EventArgs* e )
{
	Control::OnMouseHover(e);
	_state = static_cast<State>(_state | Hover);
}

void Button::OnMouseLeave( EventArgs* e )
{
	Control::OnMouseLeave(e);
	_state = static_cast<State>(_state & ~Hover);
}

void Button::OnMouseDown( MouseEventArgs* e )
{
	Control::OnMouseDown(e);
	if (e->Button == MouseButtons::Left)
		_state = static_cast<State>(_state | Pressed);
}

void Button::OnMouseEnter( EventArgs* e )
{
	Control::OnMouseEnter(e);
	_state = static_cast<State>(_state | Hover);
}

void Button::OnPaint( PaintEventArgs* e )
{
	if (_state == Hover)
	{
		set_BackColor(SystemColors::ButtonHighlight);
		Image* image = _stateImages[Hover];
		if (image == null)
			image = _stateImages[Normal];
		set_BackgroundImage(image, false);
	}	
	else if (_state == HoverPressed)
	{
		set_BackColor(SystemColors::ButtonShadow);
		Image* image = _stateImages[Pressed];
		if (image == null)
			image = _stateImages[Normal];
		set_BackgroundImage(image, false);
	}
	else
	{
		set_BackColor(SystemColors::ButtonFace);
		set_BackgroundImage(_stateImages[Normal], false);
	}

	ButtonBase::OnPaint(e);

	Graphics& g = e->Graphics;

	Drawing::Pen pen(Color::Black);
	g.DrawRectangle(pen, 1, 1, get_Size().Width - 1, get_Size().Height - 1);

	SolidBrush brush(SystemColors::ControlText);
	g.DrawString(get_Text(), *SystemFonts::DefaultFont, brush, PointF(3, 3));
}

void Button::OnMouseMove( MouseEventArgs* e )
{
	Control::OnMouseMove(e);

	if (!Drawing::Rectangle(Point::Empty, get_Size()).Contains(e->Location))
	{
		_state = static_cast<State>(_state & ~Hover);
	}
	else
	{
		_state = static_cast<State>(_state | Hover);
	}
}

void Button::OnLeave( EventArgs* e )
{
	_state = Normal;
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
	if (_stateImages[s] != null)
	{
		delete _stateImages[s];
	}
	_stateImages[s] = Image::FromFile(image);
}

Button::~Button()
{
	set_BackgroundImage(null, false);
	for (size_t i = 0; i < StateMax; ++i)
	{
		delete _stateImages[i];
		_stateImages[i] = null;
	}
}

}}}
