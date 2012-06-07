#include "FormManager.h"
#include <Windows.h>

#include "Form.h"
#include "Control.h"

#include <System.Threading/Threading.h>
using namespace mUI::System::Threading;

namespace mUI{ namespace System{  namespace Forms{

struct FormManager::Data
{
	Data()
		: activeForm(INVALID_VALUE)
		, focusedControl(INVALID_VALUE)
		, mousedControl(INVALID_VALUE)
		, mainframe(INVALID_VALUE)
		, handleCount(0)
	{}

	IntPtr activeForm;
	IntPtr focusedControl;
	IntPtr mousedControl;
	IntPtr mainframe;
	IntPtr handleCount;

	deque<Form*> formList;
	map<IntPtr, Control*> handleMap;

	static FormManager* instance;
};

FormManager* FormManager::Data::instance = null;

FormManager::FormManager() 
	: _d(new Data())
{
}

FormManager::~FormManager()
{
	delete _d;
}

FormManager& FormManager::get_Instance()
{
	assert(Data::instance != null);
	return *Data::instance;
}

void FormManager::set_RootForm( Form& form )
{
	_d->mainframe = form.get_Handle();
	_d->focusedControl = _d->mainframe;
	_d->activeForm = _d->mainframe;
}

Form* FormManager::get_ActiveForm() const
{
	return reinterpret_cast<Form*>(Control::FromHandle(_d->activeForm));
}

void FormManager::RegisterForm( Form& form )
{
	for (deque<Form*>::iterator iter = _d->formList.begin();
		iter != _d->formList.end(); ++iter)
	{
		if (*iter == &form)
		{
			assert(!"Form registered twice!");
		}
	}

	for (deque<Form*>::iterator iter = _d->formList.begin();
		iter != _d->formList.end(); ++iter)
	{
		if (!(*iter)->get_TopMost())
		{
			_d->formList.insert(iter, &form);
			return;
		}
	}
	_d->formList.push_back(&form);		// 1st form.
}

void FormManager::UnregisterForm( Form& form )
{
	for (deque<Form*>::iterator iter = _d->formList.begin();
		iter != _d->formList.end(); ++iter)
	{
		if (*iter == &form)
		{
			_d->formList.erase(iter);
			return;
		}
	}
	assert(!"No form matched!");
}

void FormManager::BringToFront( Form& form )
{
	if (form.get_TopMost())
		return;

	deque<Form*>::iterator target = _d->formList.end(), swap_to = _d->formList.end();

	for (deque<Form*>::iterator iter = _d->formList.begin(); iter != _d->formList.end(); ++iter)
	{
		if (*iter == &form)
		{
			target = iter; break;
		}
	}
	if (target == _d->formList.end())
		assert(!"What have you put here, a dinosaur?");
	_d->formList.erase(target);

	for (deque<Form*>::iterator iter = _d->formList.begin(); iter != _d->formList.end(); ++iter)
	{
		if (*iter != &form && !(*iter)->get_TopMost())
		{
			swap_to = iter; break;
		}
	}
	_d->formList.insert(swap_to, &form);
}

Form* FormManager::FormAt( const Point& location )
{
	for (deque<Form*>::iterator iter = _d->formList.begin();
		iter != _d->formList.end(); ++iter)
	{
		assert(*iter != null);
		Form& form = **iter;
		if (form.get_Visible() && Drawing::Rectangle(form.get_Location(), form.get_Size()).Contains(location))
		{
			return &form;
		}
	}
	return null;
}

Control* FormManager::ControlAt( const Point& pt )
{
	Form* form = FormAt(pt);
	if (form == null)
		return null;
	Control* control = form->GetChildAtPoint(pt - form->get_Location());
	if (control == null)
		return form;
	return control;
}

Point FormManager::DeleteMe_GetControlFrameCoord( const Control& control )
{
	const Control* c = &control;

	Point coord = c->get_Location();
	while (c->get_Parent() != null)
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
        RaiseMouseLeaveEvent();
		break;

	case WM_MOUSEMOVE:
        RaiseMouseMoveEvent(pt);
		break;

	case WM_LBUTTONDOWN:
        RaiseLButtonDownEvent(pt);
		break;

	case WM_LBUTTONUP:
        RaiseLBottonUpEvent(pt);
		break;

	case WM_RBUTTONDOWN:
        RaiseRButtonDownEvent(pt);
		break;

	case WM_RBUTTONUP:
        RaiseRButtonUpEvent(pt);
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
			Control* ctrl = FromHandle(_d->focusedControl);
			while (ctrl != null && ctrl->get_Handle() != _d->mainframe)
			{
				ctrl->OnKeyPress(&e);
				if (e.Handled)
					break;
				ctrl = ctrl->get_Parent();
			}
			if (!e.Handled)
			{
				Form* mainframe = reinterpret_cast<Form*>(FromHandle(_d->mainframe));
				mainframe->OnKeyPress(&e);
			}
		}
		break;
	}
}

void FormManager::DoEvents()
{
	for (map<IntPtr, Control*>::iterator iter = _d->handleMap.begin();
		iter != _d->handleMap.end(); ++iter)
	{
		Control* control = iter->second;
		assert(control != null);
		control->_InvokeAll();
	}
}

void FormManager::OnFrameActivated()
{
	Control* focused = Control::FromHandle(_d->focusedControl);
	if (focused != null)
	{
		Control::_Activate(*focused);
	}
	else
	{
		_d->activeForm = _d->mainframe;
		_d->focusedControl = _d->mainframe;
	}
}

void FormManager::OnFrameDeactivated()
{
	Control* focused = Control::FromHandle(_d->focusedControl);
	if (focused != null)
	{
		Control::_Deactivate(*focused);
	}
}

void FormManager::Dispose()
{
	for (int i = 0; i < 3; ++i)
		Data::instance->DoEvents();

	while (Data::instance->_d->formList.size() > 0)
	{
		delete Data::instance->_d->formList.front();
	}

	delete Data::instance;
	Data::instance = null;
}

void FormManager::Render()
{
	for (deque<Form*>::reverse_iterator iter = _d->formList.rbegin();
		iter != _d->formList.rend(); ++iter)
	{
		assert(*iter);
		Form& form = **iter;
		form.Refresh();
	}
}

bool FormManager::Initialize()
{
	assert(Data::instance == null);
	Data::instance = new FormManager();
	return Data::instance != null;
}

IntPtr FormManager::RegisterControl( Control& ctrl )
{
	IntPtr handle = Interlocked::Increment(_d->handleCount);
	_d->handleMap[handle] = &ctrl;
	return handle;
}

void FormManager::UnregisterControl( Control& ctrl )
{
	map<IntPtr, Control*>::iterator iter = _d->handleMap.find(ctrl.get_Handle());
	assert(iter != _d->handleMap.end());
	iter->second = null;
	_d->handleMap.erase(iter);
}

Control* FormManager::FromHandle( const IntPtr& h )
{
	map<IntPtr, Control*>::iterator iter = _d->handleMap.find(h);
	if (iter == _d->handleMap.end())
		return null;
	else
		return iter->second;
}

Form* FormManager::get_Form(IntPtr handle)
{
	for (deque<Form*>::iterator iter = _d->formList.begin();
		iter != _d->formList.end(); ++iter)
	{
		Form* f = *iter;
		if (f->get_Handle() == handle)
			return f;
	}
	return null;
}

const Form* FormManager::get_Form( IntPtr handle ) const
{
	for (deque<Form*>::iterator iter = _d->formList.begin();
		iter != _d->formList.end(); ++iter)
	{
		Form* f = *iter;
		if (f->get_Handle() == handle)
			return f;
	}
	return null;
}

Form* FormManager::get_RootForm()
{
    return get_Form(_d->mainframe);
}

Point FormManager::MapWindowPoint( IntPtr from, IntPtr to, const Point& pt )
{
	const Control* fromCtrl = FromHandle(from);
	if (fromCtrl == null)
		throw ArgumentException(L"From control can't be found.");
	const Control* toCtrl = FromHandle(to);
	const Control* commonParent = FindCommonParent(fromCtrl, toCtrl);

	Point mapOnCommonParent = MapWindowPointToAncestor(fromCtrl, commonParent, pt);
	if (toCtrl == null)
		return mapOnCommonParent;

	Point toCtrlOnCommonParent = MapWindowPointToAncestor(toCtrl, commonParent, Point::Empty);
	return mapOnCommonParent + toCtrlOnCommonParent;
}

const Control* FormManager::FindCommonParent( const Control* from, const Control* to )
{
	if (from == null || to == null)
		return null;
	map<IntPtr, const Control*> fromParents;
	for (const Control* ctrl = from; ctrl != null; ctrl = ctrl->get_Parent())
	{
		fromParents[ctrl->get_Handle()] = ctrl;
	}
	for (const Control* ctrl = to; ctrl != null; ctrl = ctrl->get_Parent())
	{
		if (fromParents.find(ctrl->get_Handle()) != fromParents.end())
		{
			return ctrl;
		}
	}
	return null;
}

Point FormManager::MapWindowPointToAncestor( const Control* fromCtrl, 
	const Control* commonParent, Point pt )
{
	for (const Control* control = fromCtrl; 
		control != commonParent; 
		control = control->get_Parent())
	{
		pt += control->get_Location();
	}
	return pt;
}

mUI::IntPtr FormManager::GetFocusedHandle() const
{
	return _d->focusedControl;
}

void FormManager::SetFocus( IntPtr value )
{
	Control* prevControl = FromHandle(_d->focusedControl);
	if (prevControl != null)
	{
		prevControl->OnLostFocus(&EventArgs::Empty);
		prevControl->OnLeave(&EventArgs::Empty);
		prevControl->OnValidating(&EventArgs::Empty);
		prevControl->OnValidated(&EventArgs::Empty);
	}

	Control* focusedControl = FromHandle(value);
	if (focusedControl == null)
		throw new ArgumentException(L"Invalid handle");
	_d->focusedControl = value;
	focusedControl->OnEnter(&EventArgs::Empty);
	focusedControl->OnGotFocus(&EventArgs::Empty);

	Control* control = focusedControl->get_Parent();
	while (control != null)
	{
		control->OnEnter(&EventArgs::Empty);
		control = control->get_Parent();
	}
}

void FormManager::RaiseMouseLeaveEvent()
{
    Control* mouse_leave = Control::FromHandle(_d->mousedControl);
    if (mouse_leave != null)
        mouse_leave->OnMouseLeave(&EventArgs::Empty);
    _d->mousedControl = INVALID_VALUE;
}

void FormManager::RaiseMouseMoveEvent( Point pt )
{
    // Triggers MouseEnter & MouseLeave
    Control* enter_control = ControlAt(pt);
    if (enter_control != null)
    {
        if (enter_control->get_Handle() != _d->mousedControl)
        {
            Control* leave_control = Control::FromHandle(_d->mousedControl);
            if (leave_control != null)
                leave_control->OnMouseLeave(&EventArgs::Empty);
            _d->mousedControl = enter_control->get_Handle();
            enter_control->OnMouseEnter(&EventArgs::Empty);
        }
    }
    else
    {
        Control* mouse_leave = Control::FromHandle(_d->mousedControl);
        if (mouse_leave != null)
            mouse_leave->OnMouseLeave(&EventArgs::Empty);
        _d->mousedControl = INVALID_VALUE;
    }

    // Triggers MouseMove
    Control* focused_control_control = Control::FromHandle(_d->focusedControl);
    if (focused_control_control != null)
    {
        MouseEventArgs mea;
        mea.Location = pt - DeleteMe_GetControlFrameCoord(*focused_control_control);
        mea.Button = MouseButtons::None;			// TODO:
        mea.Clicks = 0;
        mea.Delta = 0;							// TODO:
        focused_control_control->OnMouseMove(&mea);
    }
}

void FormManager::RaiseLButtonDownEvent( Point pt )
{
    RaiseMouseButtonDownEvent(MouseButtons::Left, pt);
}

void FormManager::RaiseLBottonUpEvent( Point pt )
{
    Control* control = Control::FromHandle(_d->focusedControl);
    if (control == null)
        control = ControlAt(pt);
    if (control != null)
    {
        MouseEventArgs mea;
        mea.Button = MouseButtons::Left;
        mea.Clicks = 1;
        mea.Delta = 0;
        mea.Location = pt - DeleteMe_GetControlFrameCoord(*control);
        control->OnMouseUp(&mea);
    }
}

void FormManager::RaiseRButtonDownEvent( Point pt )
{
    RaiseMouseButtonDownEvent(MouseButtons::Right, pt);
}

void FormManager::RaiseRButtonUpEvent( Point pt )
{
    Control* control = Control::FromHandle(_d->focusedControl);
    if (control == null)
        control = ControlAt(pt);
    if (control != null)
    {
        MouseEventArgs mea;
        mea.Button = MouseButtons::Right;
        mea.Clicks = 1;
        mea.Delta = 0;
        mea.Location = pt - DeleteMe_GetControlFrameCoord(*control);
        control->OnMouseUp(&mea);
    }
}

void FormManager::RaiseMouseButtonDownEvent( MouseButtons button, Point pt )
{
    Control* lbtn_control = ControlAt(pt);
    if (lbtn_control != null)
    {
        if (lbtn_control->get_Handle() != _d->focusedControl)
        {
            Control* lostf_control = Control::FromHandle(_d->focusedControl);
            if (lostf_control != null)
                Control::_Deactivate(*lostf_control);

            Control::_Activate(*lbtn_control);

            Form& form = lbtn_control->FindForm();
            if (form.get_Handle() != _d->mainframe)
                form.BringToFront();
            _d->focusedControl = lbtn_control->get_Handle();
        }

        MouseEventArgs mea;
        mea.Button = button;
        mea.Delta = 0;
        mea.Location = pt - DeleteMe_GetControlFrameCoord(*lbtn_control);
        mea.Clicks = 1;
        lbtn_control->OnMouseDown(&mea);
    }
}

}}}
