#include "Form.h"

#include "Application.h"
#include "SystemInformation.h"

#include "../Drawing/Drawing.h"
using mUI::System::Drawing::Pen;

#include "FormManager.h"

namespace mUI{ namespace System{  namespace Forms{

Form::Form() : topmost_(false)
{
	FormManager::get_Instance().RegisterForm(*this);
	InitializeComponent();
	//BeginInvoke(MethodInvoker(this, &Form::OnLoad, &EventArgs::Empty));
}

Form::~Form(void)
{
	if (get_Visible())
		Hide();

	FormManager::get_Instance().UnregisterForm(*this);
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
			//g.FillRectangle(brush, 1, 1, get_Size().Width - border_size * 2, caption_height - border_size);
		}
	}
}

void Form::InitializeComponent()
{
	set_Size(Drawing::Size(default_width, default_height));
	set_FormBorderStyle(FormBorderStyle::FixedSingle);			// TODO: Default should be Sizable
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
	switch (get_FormBorderStyle())
	{
	case FormBorderStyle::None:
		break;

	case FormBorderStyle::FixedSingle:
		pt.X += SystemInformation::GetBorderSize();
		pt.Y += SystemInformation::GetBorderSize()/* + SystemInformation::GetCaptionHeight()*/;
		break;
	}
	pt += get_Location();
	return pt;
}

Graphics* Form::CreateGraphics()
{
	return Drawing::CreateGraphics(Drawing::Rectangle(get_Location(), get_Size()));
}

Form* Form::get_ActiveForm()
{
	return FormManager::get_Instance().get_ActiveForm();
}

}}}
