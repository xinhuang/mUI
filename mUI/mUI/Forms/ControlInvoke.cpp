#include "Control.h"

#include "../Threading/Threading.h"
using namespace mUI::System::Threading;

#include "SystemInformation.h"
#include "Application.h"
#include "Form.h"
#include "FormManager.h"

// ------------------------------------------------------- //

namespace mUI{ namespace System { namespace Forms{

class Control::Task
{
public:
	Task(const Delegate<>& method)
	{
		method_ = method;
	}
	void Invoke()
	{
		method_();
	}

private:
	Delegate<> method_;
};

void Control::InvokeHelper( const Delegate<>& method, bool fSynchronous )
{
	{
		AutoLock lock(this);
		qutaskinvoke_.push(new Task(method));
	}

	if (!InvokeRequired())
	{
		_InvokeAll();
	}
}

void Control::_InvokeAll()
{
	AutoLock lock(this);
	while (!qutaskinvoke_.empty())
	{
		Task* task = qutaskinvoke_.front();
		qutaskinvoke_.pop();
		assert(task != NULL);
		task->Invoke();
		delete task;
	}
}

bool Control::InvokeRequired() const
{
	return Thread::get_ManagedThreadID() != thread_;
}

void Control::Invoke( const Delegate<void>& method )
{
	InvokeHelper(method, false);
}

}}}
