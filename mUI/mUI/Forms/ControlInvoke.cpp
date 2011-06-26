#include "Control.h"

#include "../IAsyncResult.h"
using namespace mUI::System;

#include "../Threading/Threading.h"
using namespace mUI::System::Threading;

// ------------------------------------------------------- //

namespace mUI{ namespace System { namespace Forms{

class Control::Task
{
public:
	Task(const Delegate<>& method, bool synchronous);
	~Task()
	{
		async_result_ = NULL;
	}

	void Invoke();
	IAsyncResult* get_AsyncResult();

private:
	class AsyncResult : public IAsyncResult
	{
		friend Task;

	public:
		AsyncResult(Task& binds) : task_(&binds)
		{}

		virtual ~AsyncResult();
		virtual WaitHandle* get_AsyncWaitHandle();
		virtual bool get_IsComplete() const;

	private:
		Task* task_;
		EventWaitHandle wait_handle_;
		bool completed_;
	};

private:
	Delegate<> method_;
	AsyncResult* async_result_;
};

// ---------------------------------------------------------------------- //

Control::Task::Task(const Delegate<>& method, bool synchronous)
{
	method_ = method;
	if (synchronous)
	{
		async_result_ = new AsyncResult(*this);
	}
	else
	{
		async_result_ = NULL;
	}
}

void Control::Task::Invoke()
{
	method_();
	if (async_result_ != NULL)
	{
		async_result_->completed_ = true;
		async_result_->wait_handle_.Set();
	}
}

IAsyncResult* Control::Task::get_AsyncResult()
{
	return async_result_;
}

Control::Task::AsyncResult::~AsyncResult()
{
	task_->async_result_ = NULL;
}

WaitHandle* Control::Task::AsyncResult::get_AsyncWaitHandle()
{
	return &wait_handle_;
}

bool Control::Task::AsyncResult::get_IsComplete() const
{
	return completed_;
}
// ---------------------------------------------------------------------- //

IAsyncResult* Control::InvokeHelper( const Delegate<>& method, bool fSynchronous )
{
	Task* task = new Task(method, fSynchronous);
	IAsyncResult* async_result = task->get_AsyncResult();
	{
		AutoLock lock(this);
		qutaskinvoke_.push(task);
	}

	if (!get_InvokeRequired())
	{
		_InvokeAll();
	}

	return async_result;
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

bool Control::get_InvokeRequired() const
{
	return Thread::get_ManagedThreadID() != thread_;
}

void Control::Invoke( const Delegate<void>& method )
{
	IAsyncResult* r = InvokeHelper(method, true);
	r->get_AsyncWaitHandle()->WaitOne();
	delete r;
}

IAsyncResult* Control::BeginInvoke( const Delegate<void>& method )
{
	return InvokeHelper(method, true);
}

void Control::EndInvoke( IAsyncResult& asyncResult )
{
	WaitHandle* wait_handle = asyncResult.get_AsyncWaitHandle();
	wait_handle->WaitOne();
}

}}}
