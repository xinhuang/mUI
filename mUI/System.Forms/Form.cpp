#include "Form.h"

#include "Application.h"
#include "SystemInformation.h"

#include <System.Drawing/Drawing.h>
using mUI::System::Drawing::Pen;

#include "FormManager.h"

namespace mUI{ namespace System{  namespace Forms{

struct Form::Data
{
	Data()
		: dragMove(false)
		, moving(false)
	{}

	bool dragMove;
	bool moving;
	Point mouseDownLocation;
};

Form::Form() 
	: topmost_(false), _d(new Data())
{
	FormManager::get_Instance().RegisterForm(*this);
	InitializeComponent();
}

Form::~Form(void)
{
	if (get_Visible())
		Hide();

	FormManager::get_Instance().UnregisterForm(*this);

	delete _d;
}

void Form::Close()
{
	OnClosing(&EventArgs::Empty);
	Hide();
	OnClosed(&EventArgs::Empty);
}

void Form::OnPaint( PaintEventArgs* e )
{
	Control::OnPaint(e);

	Graphics& g = e->Graphics;

	switch (get_FormBorderStyle())
	{
	case FormBorderStyle::FixedSingle:
		{
			int border_size = SystemInformation::GetBorderSize();
			Pen pen(Color::Black);
			g.DrawRectangle(pen, 1, 1, get_Size().Width - 1, get_Size().Height - 1);

			int caption_height = SystemInformation::GetCaptionHeight();
			SolidBrush brush(Color::Grey);
		}
	}
}

void Form::InitializeComponent()
{
	set_Size(Drawing::Size(default_width, default_height));
}

void Form::OnEnter( EventArgs* e )
{
	// Suppress Enter event.
	OnActivated(e);
}

void Form::OnLeave( EventArgs* e )
{
	// Suppress Leave event.
	OnDeactivate(e);
}

void Form::OnActivated( EventArgs* e )
{
	Activated(this, e);
}

void Form::OnDeactivate( EventArgs* e )
{
	Deactivate(this, e);
}

void Form::set_FormBorderStyle( const FormBorderStyle& style )
{
	if (get_FormBorderStyle() != style)
	{
		form_boarder_style_ = style;
		OnBorderStyleChanged(&EventArgs::Empty);
	}
}

const FormBorderStyle& Form::get_FormBorderStyle() const
{
	return form_boarder_style_;
}

void Form::OnBorderStyleChanged( EventArgs* e )
{
	switch (get_FormBorderStyle())
	{
	case FormBorderStyle::None:
		{
		}
		break;

	default:
		{
		}
		break;
	}
	BorderStyleChanged(this, e);
}

Size Form::get_ClientSize() const
{
	Size cs = get_Size();
	switch (get_FormBorderStyle())
	{
	case FormBorderStyle::None:
		break;

	case FormBorderStyle::FixedSingle:
		cs.Width -= SystemInformation::GetBorderSize() * 2;
		cs.Height -= SystemInformation::GetBorderSize() * 2/* - SystemInformation::GetCaptionHeight()*/; 
		break;
	}
	return cs;
}

void Form::set_TopMost( bool value )
{
	topmost_ = value;
}

void Form::OnClosed( EventArgs* e )
{
	Closed(this, e);
}

void Form::OnClosing( EventArgs* e )
{
	Closing(this, e);
}

void Form::OnLoad( EventArgs* e )
{
	Load(this, e);
}

Point Form::PointToScreen( Point pt ) const
{
    pt += get_Location();
	switch (get_FormBorderStyle())
	{
	case FormBorderStyle::None:
		break;

	case FormBorderStyle::FixedSingle:
		pt.X += SystemInformation::GetBorderSize();
		pt.Y += SystemInformation::GetBorderSize()/* + SystemInformation::GetCaptionHeight()*/;
		break;
	}
	return pt;
}

Form* Form::get_ActiveForm()
{
	return FormManager::get_Instance().get_ActiveForm();
}

void Form::OnMouseDown( MouseEventArgs* e )
{
	if (_d->dragMove && e->Button == MouseButtons::Left)
	{
		_d->moving = true;
		_d->mouseDownLocation = e->Location;
	}
}

void Form::OnMouseUp( MouseEventArgs* e )
{
	if (e->Button == MouseButtons::Left && _d->dragMove)
		_d->moving = false;
}

void Form::OnMouseMove( MouseEventArgs* e )
{
	if (_d->moving && _d->dragMove)
		set_Location(get_Location() + e->Location - _d->mouseDownLocation);
}

bool Form::get_DragMove() const
{
	return _d->dragMove;
}

void Form::set_DragMove( bool value )
{
	_d->dragMove = value;
	_d->moving = false;
}

}}}
