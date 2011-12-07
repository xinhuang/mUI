#include "FormManager.h"
#include <Windows.h>

#include "Form.h"
#include "Control.h"

#include <System.Threading/Threading.h>
using namespace mUI::System::Threading;

namespace mUI{ namespace System{  namespace Forms{

FormManager* FormManager::instance_ = NULL;

FormManager& FormManager::get_Instance()
{
	return *instance_;
}

void FormManager::set_RootForm( Form& form )
{
	mainframe_ = form.get_Handle();
	focused_control_ = mainframe_;
	active_form_ = mainframe_;
}

Form* FormManager::get_ActiveForm() const
{
	return reinterpret_cast<Form*>(Control::FromHandle(active_form_));
}

void FormManager::RegisterForm( Form& form )
{
	for (deque<Form*>::iterator iter = form_list_.begin();
		iter != form_list_.end(); ++iter)
	{
		if (*iter == &form)
		{
			assert(!"Form registered twice!");
		}
	}

	for (deque<Form*>::iterator iter = form_list_.begin();
		iter != form_list_.end(); ++iter)
	{
		if (!(*iter)->get_TopMost())
		{
			form_list_.insert(iter, &form);
			return;
		}
	}

	form_list_.push_back(&form);		// 1st form.
}

void FormManager::UnregisterForm( Form& form )
{
	for (deque<Form*>::iterator iter = form_list_.begin();
		iter != form_list_.end(); ++iter)
	{
		if (*iter == &form)
		{
			form_list_.erase(iter);
			return;
		}
	}
	assert(!"No form matched!");
}

void FormManager::BringToFront( Form& form )
{
	if (form.get_TopMost())
		return;

	deque<Form*>::iterator target = form_list_.end(), swap_to = form_list_.end();

	for (deque<Form*>::iterator iter = form_list_.begin(); iter != form_list_.end(); ++iter)
	{
		if (*iter == &form)
		{
			target = iter; break;
		}
	}
	if (target == form_list_.end())
		assert(!"What have you put here, a dinosaur?");
	form_list_.erase(target);

	for (deque<Form*>::iterator iter = form_list_.begin(); iter != form_list_.end(); ++iter)
	{
		if (*iter != &form && !(*iter)->get_TopMost())
		{
			swap_to = iter; break;
		}
	}
	form_list_.insert(swap_to, &form);
}

Form* FormManager::FormAt( const Point& location )
{
	for (deque<Form*>::iterator iter = form_list_.begin();
		iter != form_list_.end(); ++iter)
	{
		assert(*iter != NULL);
		Form& form = **iter;
		if (form.get_Visible() && Drawing::Rectangle(form.get_Location(), form.get_Size()).Contains(location))
		{
			return &form;
		}
	}
	return NULL;
}

Control* FormManager::ControlAt( const Point& pt )
{
	Form* form = FormAt(pt);
	if (form == NULL)
		return NULL;
	Control* control = form->GetChildAtPoint(pt - form->get_Location());
	if (control == NULL)
		return form;
	return control;
}

Point FormManager::DeleteMe_GetControlFrameCoord( const Control& control )
{
	const Control* c = &control;

	Point coord = c->get_Location();
	while (c->get_Parent() != NULL)
	{
		coord += c->get_Parent()->get_Location();
		c = c->get_Parent();
	}
	return coord;
}

void FormManager::RaiseMouseEvent( unsigned int message, IntPtr wParam, IntPtr lParam )
{
	int16_t x = LOWORD(lParam), y = HIWORD(lParam);
	Point pt(x, y);
	switch (message)
	{
	case WM_MOUSELEAVE:
		{
			Control* mouse_leave = Control::FromHandle(moused_control_);
			if (mouse_leave != NULL)
				mouse_leave->OnMouseLeave(&EventArgs::Empty);
			moused_control_ = INVALID_VALUE;
		}
		break;

	case WM_MOUSEMOVE:
		{
			// Triggers MouseEnter & MouseLeave
			Control* enter_control = ControlAt(pt);
			if (enter_control != NULL)
			{
				if (enter_control->get_Handle() != moused_control_)
				{
					Control* leave_control = Control::FromHandle(moused_control_);
					if (leave_control != NULL)
						leave_control->OnMouseLeave(&EventArgs::Empty);
					moused_control_ = enter_control->get_Handle();
					enter_control->OnMouseEnter(&EventArgs::Empty);
				}
			}
			else
			{
				Control* mouse_leave = Control::FromHandle(moused_control_);
				if (mouse_leave != NULL)
					mouse_leave->OnMouseLeave(&EventArgs::Empty);
				moused_control_ = INVALID_VALUE;
			}

			// Triggers MouseMove
			Control* focused_control_control = Control::FromHandle(focused_control_);
			if (focused_control_control != NULL)
			{
				MouseEventArgs mea;
				mea.Location = pt - DeleteMe_GetControlFrameCoord(*focused_control_control);
				mea.Button = MouseButtons::None;			// TODO:
				mea.Clicks = 0;
				mea.Delta = 0;							// TODO:
				focused_control_control->OnMouseMove(&mea);
			}
		}
		break;

	case WM_LBUTTONDOWN:
		{
			Control* lbtn_control = ControlAt(pt);
			if (lbtn_control != NULL)
			{
				if (lbtn_control->get_Handle() != focused_control_)
				{
					Control* lostf_control = Control::FromHandle(focused_control_);
					if (lostf_control != NULL)
						Control::_Deactivate(*lostf_control);

					Control::_Activate(*lbtn_control);

					Form& form = lbtn_control->FindForm();
					if (form.get_Handle() != mainframe_)
						form.BringToFront();
					focused_control_ = lbtn_control->get_Handle();
				}

				MouseEventArgs mea;
				mea.Button = MouseButtons::Left;
				mea.Delta = 0;
				mea.Location = pt - DeleteMe_GetControlFrameCoord(*lbtn_control);
				mea.Clicks = 1;
				lbtn_control->OnMouseDown(&mea);
			}
		}
		break;

	case WM_LBUTTONUP:
		{
			Control* control = Control::FromHandle(focused_control_);
			if (control == NULL)
				control = ControlAt(pt);
			if (control != NULL)
			{
				MouseEventArgs mea;
				mea.Button = MouseButtons::Left;
				mea.Clicks = 1;
				mea.Delta = 0;
				mea.Location = pt - DeleteMe_GetControlFrameCoord(*control);
				control->OnMouseUp(&mea);
			}
		}
		break;

	case WM_RBUTTONDOWN:
		{
			Control* lbtn_control = ControlAt(pt);
			if (lbtn_control != NULL)
			{
				if (lbtn_control->get_Handle() != focused_control_)
				{
					Control* lostf_control = Control::FromHandle(focused_control_);
					if (lostf_control != NULL)
						Control::_Deactivate(*lostf_control);

					Control::_Activate(*lbtn_control);

					Form& form = lbtn_control->FindForm();
					if (form.get_Handle() != mainframe_)
						form.BringToFront();
					focused_control_ = lbtn_control->get_Handle();
				}

				MouseEventArgs mea;
				mea.Button = MouseButtons::Right;
				mea.Delta = 0;
				mea.Location = pt - DeleteMe_GetControlFrameCoord(*lbtn_control);
				mea.Clicks = 1;
				lbtn_control->OnMouseDown(&mea);
			}
		}
		break;

	case WM_RBUTTONUP:
		{
			Control* control = Control::FromHandle(focused_control_);
			if (control == NULL)
				control = ControlAt(pt);
			if (control != NULL)
			{
				MouseEventArgs mea;
				mea.Button = MouseButtons::Right;
				mea.Clicks = 1;
				mea.Delta = 0;
				mea.Location = pt - DeleteMe_GetControlFrameCoord(*control);
				control->OnMouseUp(&mea);
			}
		}
		break;
	}
}

void FormManager::RaiseKeyboardEvent( unsigned int message, IntPtr wParam, IntPtr lParam )
{
	switch (message)
	{
	case WM_KEYDOWN:
		break;

	case WM_KEYUP:
		break;

	case WM_CHAR:
		{
			KeyPressEventArgs e(reinterpret_cast<char>(wParam));
			Control* ctrl = FromHandle(focused_control_);
			while (ctrl != NULL && ctrl->get_Handle() != mainframe_)
			{
				ctrl->OnKeyPress(&e);
				if (e.Handled)
					break;
				ctrl = ctrl->get_Parent();
			}
			if (!e.Handled)
			{
				Form* mainframe = reinterpret_cast<Form*>(FromHandle(mainframe_));
				mainframe->OnKeyPress(&e);
			}
		}
		break;
	}
}

void FormManager::DoEvents()
{
	for (map<IntPtr, Control*>::iterator iter = handle_map_.begin();
		iter != handle_map_.end(); ++iter)
	{
		Control* control = iter->second;
		assert(control != NULL);
		control->_InvokeAll();
	}
}

void FormManager::OnFrameActivated()
{
	Control* focused = Control::FromHandle(focused_control_);
	if (focused != NULL)
	{
		Control::_Activate(*focused);
	}
	else
	{
		active_form_ = mainframe_;
		focused_control_ = mainframe_;
	}
}

void FormManager::OnFrameDeactivated()
{
	Control* focused = Control::FromHandle(focused_control_);
	if (focused != NULL)
	{
		Control::_Deactivate(*focused);
	}
}

FormManager::FormManager() : 
	active_form_(INVALID_VALUE), 
	focused_control_(INVALID_VALUE), 
	moused_control_(INVALID_VALUE),
	mainframe_(INVALID_VALUE),
	handle_count_(INVALID_VALUE)
{
}

void FormManager::Dispose()
{
	for (int i = 0; i < 3; ++i)
		instance_->DoEvents();

	while (instance_->form_list_.size() > 0)
	{
		delete instance_->form_list_.front();
	}

	delete instance_;
	instance_ = NULL;
}

void FormManager::Render()
{
	for (deque<Form*>::reverse_iterator iter = form_list_.rbegin();
		iter != form_list_.rend(); ++iter)
	{
		assert(*iter);
		Form& form = **iter;
		form.Refresh();
	}
}

bool FormManager::Initialize()
{
	assert(instance_ == NULL);
	instance_ = new FormManager();
	return instance_ != NULL;
}

IntPtr FormManager::RegisterControl( Control& ctrl )
{
	IntPtr handle = Interlocked::Increment(handle_count_);
	handle_map_[handle] = &ctrl;
	return handle;
}

void FormManager::UnregisterControl( Control& ctrl )
{
	map<IntPtr, Control*>::iterator iter = handle_map_.find(ctrl.get_Handle());
	assert(iter != handle_map_.end());
	iter->second = NULL;
	handle_map_.erase(iter);
}

Control* FormManager::FromHandle( const IntPtr& h )
{
	map<IntPtr, Control*>::iterator iter = handle_map_.find(h);
	if (iter == handle_map_.end())
		return NULL;
	else
		return iter->second;
}

FormManager::~FormManager()
{

}

}}}
