#include "Control.h"

#include <System.Drawing/Drawing.h>
using namespace mUI::System::Drawing;

#include <System.Threading/Threading.h>
using namespace mUI::System::Threading;

#include "SystemInformation.h"
#include "Application.h"
#include "Form.h"
#include "FormManager.h"

// -------------------------------------------------------------- //

namespace mUI{ namespace System{  namespace Forms{

// warning C4355: 'this' : used in base member initializer list
#pragma warning(disable: 4355)

Control::Control() : 
	parent_(NULL), Controls(*this), visibility_(false), 
	back_color_(SystemColors::Control), background_image_(NULL),
	background_image_layout_(ImageLayout::None),
	suspend_layout_count_(0)
{
	thread_ = Threading::Thread::get_ManagedThreadID();
	handle_ = FormManager::get_Instance().RegisterControl(*this);
}

#pragma warning(default: 4355)

Control::~Control()
{
	SuspendLayout();
	FormManager::get_Instance().UnregisterControl(*this);

	delete background_image_;
	background_image_ = NULL;

	Control* parent = get_Parent();
	if (parent != NULL)
		parent->Controls.Remove(*this);
	ResumeLayout();
}

void Control::OnPaint( PaintEventArgs* e )
{
	Graphics& g = e->Graphics;
	const Drawing::Rectangle& bounds = e->ClipRectangle;

	SolidBrush brush(get_BackColor());
	g.FillRectangle(brush, bounds);

	if (get_BackgroundImage() != NULL)
	{
		switch (get_BackgroundImageLayout())
		{
		case ImageLayout::Stretch:
			g.DrawImage(*get_BackgroundImage(), bounds);
			break;

		case ImageLayout::None:
			g.DrawImage(*get_BackgroundImage(), Point::Empty);
			break;
		}
	}

	Paint(this, e);
}

void Control::OnLayout( LayoutEventArgs* e )
{
	if (suspend_layout_count_ == 0)
	{
		Layout(this, e);
		for (ControlCollection::iterator iter = Controls.begin();
			iter != Controls.end(); ++iter)
		{
			Control* control = *iter;
			control->OnLayout(e);
		}
	}
}

void Control::OnControlAdded( ControlEventArgs* e )
{
	ControlAdded(this, e);
}

void Control::OnControlRemoved( ControlEventArgs* e )
{
	ControlRemoved(this, e);
}

void Control::OnSizeChanged( EventArgs* e )
{
	SizeChanged(this, e);
}

void Control::set_Size( const Drawing::Size& size )
{
	if (size_ != size)
	{
		size_ = size; 
		OnSizeChanged(&EventArgs::Empty);
		PerformLayout(this, L"Size");
	}
}

const Color& Control::get_BackColor() const
{
	return back_color_;
}

void Control::set_BackColor( const Color& color )
{
	if (back_color_ != color)
	{
		back_color_ = color;
		OnBackColorChanged(&EventArgs::Empty);
	}
}

void Control::OnBackColorChanged( EventArgs* e )
{
	BackColorChanged(this, e);
}

void Control::Refresh()
{
	if (!get_Visible())
		return;

	Drawing::Rectangle clip(Point::Empty, this->get_Size());
	PaintEventArgs e(CreateGraphics(), clip);
	OnPaint(&e);
	delete &e.Graphics;

	for (ControlCollection::reverse_iterator iter = Controls.rbegin();
		iter != Controls.rend(); ++iter)
	{
		Control* control = *iter;
		assert(control != NULL);
		control->Refresh();
	}
}

Graphics* Control::CreateGraphics()
{
	return Drawing::CreateGraphics(Drawing::Rectangle(PointToScreen(Point::Empty), get_Size()));
}

const Point& Control::get_Location() const
{
	return location_;
}

void Control::Update()
{
	Refresh();
}

const Control* Control::GetChildAtPoint( const Point& pt ) const
{
	for (ControlCollection::const_iterator iter = Controls.begin();
		iter != Controls.end(); ++iter)
	{
		Control* control = *iter;
		assert(control != NULL);
		Drawing::Rectangle rect(control->get_Location(), control->get_Size());
		rect = RectangleToScreen(rect);
		if (rect.Contains(pt))
		{
			return control->GetChildAtPoint(pt - rect.Location);
		}
	}
	return this;
}

Control* Control::GetChildAtPoint( const Point& pt ) 
{
	for (ControlCollection::const_iterator iter = Controls.begin();
		iter != Controls.end(); ++iter)
	{
		Control* control = *iter;
		assert(control != NULL);
		Drawing::Rectangle rect(control->get_Location(), control->get_Size());
		if (rect.Contains(pt))
		{
			return control->GetChildAtPoint(pt - rect.Location);
		}
	}
	return this;
}

const String& Control::get_Text() const
{
	return text_;
}

void Control::set_Text( const String& text )
{
	text_ = text;
	OnTextChanged(&EventArgs::Empty);
}

void Control::OnTextChanged( EventArgs* e )
{
	TextChanged(this, e);
}

void Control::OnLocationChanged( EventArgs* e )
{
	TextChanged(this, e);
}

void Control::set_Location( const Point& pt )
{
	if (location_ != pt)
	{
		location_ = pt;
		OnLocationChanged(&EventArgs::Empty);
	}
}

void Control::OnMouseEnter( EventArgs* e )
{
	MouseEnter(this, e);
}

void Control::OnMouseMove( MouseEventArgs* e )
{
	MouseMove(this, e);
}

void Control::OnMouseHover( EventArgs* e )
{
	MouseHover(this, e);
}

void Control::OnMouseDown( MouseEventArgs* e )
{
	MouseDown(this, e);
}

void Control::OnMouseUp( MouseEventArgs* e )
{
	MouseUp(this, e);
	if (get_ClientRectangle().Contains(e->Location))
	{
		OnMouseClick(e);
	}
}

void Control::OnMouseWheel( MouseEventArgs* e )
{
	MouseWheel(this, e);
}

void Control::OnMouseLeave( EventArgs* e )
{
	MouseLeave(this, e);
}

void Control::OnMouseClick( MouseEventArgs* e )
{
	MouseClick(this, e);
}

void Control::OnClick( EventArgs* e )
{
	Click(this, e);
}

Control* Control::FromHandle( const IntPtr& handle )
{
	return FormManager::get_Instance().FromHandle(handle);
}

void Control::OnVisibleChanged( EventArgs* e )
{
	VisibleChanged(this, e);
}

void Control::set_Visible( bool Value )
{
	if (get_Visible() != Value)
	{
		visibility_ = Value;
		OnVisibleChanged(&EventArgs::Empty);
	}
}

void Control::set_BackgroundImage( Drawing::Image* image )
{
	set_BackgroundImage(image, true);
}

void Control::set_BackgroundImage( Drawing::Image* image, bool delete_old )
{
	if (image != background_image_)
	{
		if (delete_old)
			delete background_image_;
		background_image_ = image;
		OnBackgroundImageChanged(&EventArgs::Empty);
	}
}

void Control::OnBackgroundImageChanged( EventArgs* e )
{
	BackgroundImageChanged(this, e);
}

void Control::set_BackgroundImageLayout( const ImageLayout& value )
{
	if (get_BackgroundImageLayout() != value)
	{
		background_image_layout_ = value;
		OnBackgroundImageLayoutChanged(&EventArgs::Empty);
	}
}

void Control::OnBackgroundImageLayoutChanged( EventArgs* e )
{
	BackgroundImageLayoutChanged(this, e);
}

void Control::_BringToFront( Control& control )
{
	ControlCollection::iterator target = Controls.end(), swap_to = Controls.end();
	for (ControlCollection::iterator iter = Controls.begin(); iter != Controls.end(); ++iter)
	{
		if (*iter == &control)
		{
			target = iter; break;
		}
	}
	for (ControlCollection::iterator iter = Controls.begin(); iter != Controls.end(); ++iter)
	{
		if (*iter != &control)
		{
			swap_to = iter; break;
		}
	}
	if (target == Controls.end())
		assert(!"Control::_BringToFront(Control&) called on a not owned sub-control!");

	if (swap_to != Controls.end())			// In case of we only have one control or only one is not top-most.
	{
		*target = *swap_to;
		*swap_to = &control;
	}
}

void Control::BringToFront()
{
	if (get_Parent() != NULL)
	{
		get_Parent()->_BringToFront(*this);
	}
	else
	{
		FormManager::get_Instance().BringToFront(*reinterpret_cast<Form*>(this));			// This is a form
	}
}

Form& Control::FindForm()
{
	Control* control = this;
	while (control->get_Parent() != NULL)
	{
		control = control->get_Parent();
	}
	return *reinterpret_cast<Form*>(control);
}

const Form& Control::FindForm() const
{
	const Control* control = this;
	while (control->get_Parent() != NULL)
	{
		control = control->get_Parent();
	}
	return *reinterpret_cast<const Form*>(control);
}

void Control::OnEnter( EventArgs* e )
{
	Enter(this, e);
}

void Control::OnLeave( EventArgs* e )
{
	Leave(this, e);
}

void Control::OnGotFocus( EventArgs* e )
{
	GotFocus(this, e);
}

void Control::OnLostFocus( EventArgs* e )
{
	LostFocus(this, e);
}

void Control::_Activate( Control& c )
{
	Control* control = &c;
	vector<Control*> enter_list;
	while (control != NULL)
	{
		enter_list.push_back(control);
		control = control->get_Parent();
	}

	for (vector<Control*>::reverse_iterator iter = enter_list.rbegin();
		iter != enter_list.rend(); ++iter)
	{
		Control* c = *iter;
		c->OnEnter(&EventArgs::Empty);
	}
}

void Control::_Deactivate( Control& c )
{
	Control* control = &c;
	vector<Control*> leave_list;
	while (control != NULL)
	{
		leave_list.push_back(control);
		control = control->get_Parent();
	}

	for (vector<Control*>::reverse_iterator iter = leave_list.rbegin();
		iter != leave_list.rend(); ++iter)
	{
		Control* c = *iter;
		c->OnLeave(&EventArgs::Empty);
	}
}

void Control::SuspendLayout()
{
	++suspend_layout_count_;
}

void Control::ResumeLayout()
{
	ResumeLayout(false);
}

void Control::ResumeLayout( bool perform_layout )
{
	if (suspend_layout_count_ > 0)
		--suspend_layout_count_;
	if (perform_layout)
		PerformLayout();
}

void Control::PerformLayout()
{
	PerformLayout(NULL, String::Empty);
}

void Control::PerformLayout( Control* affected_control, const String& affected_property )
{
	if (suspend_layout_count_ > 0)
		return;

	LayoutEventArgs e(affected_control, affected_property);
	OnLayout(&e);
}

const Size& Control::get_Size() const
{
	return size_;
}

Size Control::get_ClientSize() const
{
	return this->get_Size();
}

Drawing::Rectangle Control::get_ClientRectangle() const
{
	Drawing::Rectangle rect(Point::Empty, get_ClientSize());
	return rect;
}

Point Control::PointToScreen( Point pt ) const
{
	pt += get_Location();
	return get_Parent()->PointToScreen(pt);
}

Drawing::Rectangle Control::RectangleToScreen( Drawing::Rectangle rect ) const
{
	rect.Location = PointToScreen(rect.Location);
	return rect;
}

void Control::OnKeyPress( KeyPressEventArgs* e )
{
	KeyPress(this, e);
}

// ------------------------------------------------- //

Control::ControlCollection::~ControlCollection()
{
	while (controls_.size() > 0)
	{
		Control* c = controls_.front();
		assert(c != NULL);
		assert(c->get_Parent() == &outer_class_);
		delete c;
	}
	controls_.clear();
}

Control::ControlCollection::ControlCollection( Control& outer_class ) : outer_class_(outer_class)
{

}

void Control::ControlCollection::Add( Control& control )
{
	for (iterator iter = begin(); iter != end(); ++iter)
	{
		if (*iter == &control)
			return;
	}
	controls_.push_back(&control);
	control.parent_ = &outer_class_;
	control.set_Visible(true);

	ControlEventArgs e(control);
	outer_class_.OnControlAdded(&e);
	outer_class_.PerformLayout();
}

void Control::ControlCollection::Remove( Control& control )
{
	assert(control.parent_ == &outer_class_);

	for (vector<Control*>::iterator iter = controls_.begin();
		iter != controls_.end(); ++iter)
	{
		if (*iter == &control)
		{
			controls_.erase(iter);
			control.parent_ = NULL;
			ControlEventArgs e(control);
			outer_class_.OnControlRemoved(&e);
			outer_class_.PerformLayout();
			return;
		}
	}
}

}}}
