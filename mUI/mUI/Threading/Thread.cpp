#include "Thread.h"
#include "../../stdafx.h"
#include <process.h>

#include "../ComponentModel/InvocationList.h"
#include "AutoLock.h"
#include "Interlocked.h"

#include "GlobalTLS.h"

namespace mUI{ namespace System{  namespace Threading{

struct Thread::ThreadControlBlock : public Lockable				// Lock this if nessesary, dont use Interlocked method
{
	IntPtr ID;
    IntPtr Handle;
	bool IsBackground;
	bool IsAlive;
	bool IsThreadPoolThread;
	ThreadPriority Priority;			// TODO:
	ThreadStart ThreadStart;
	size_t ReferenceCount;
};

// ------------------------------------------------------- //

size_t Thread::foreground_thread_count_ = 0;		// Using Interlocked method to access

Thread::Thread( const ThreadStart& thread_start ) : tcb_(NULL)
{
	thread_start_ = thread_start;
}

Thread::Thread( const Thread& thread )
{
	*this = thread;
}

Thread& Thread::operator=( const Thread& thread )
{
	this->Dispose();

	if (thread.tcb_ != NULL)
	{
		AutoLock lock(*thread.tcb_);
		this->tcb_ = thread.tcb_;
		++this->tcb_->ReferenceCount;
	}
	this->thread_start_ = thread.thread_start_;

	return *this;
}

Thread::~Thread()
{
	Dispose();
}

IntPtr Thread::ManagedThreadID()
{
	return reinterpret_cast<IntPtr>(::GetCurrentThreadId());
}

LocalDataStorage Thread::AllocateDataSlot()
{
	return reinterpret_cast<LocalDataStorage>(::TlsAlloc());
}

void Thread::FreeDataSlot( const LocalDataStorage& tls )
{
	bool ret = ::TlsFree(reinterpret_cast<DWORD>(tls)) == TRUE;
	assert(ret);
}

void Thread::SetData( const LocalDataStorage& tls, void* value )
{
	bool ret = ::TlsSetValue(reinterpret_cast<DWORD>(tls), value) == TRUE;
	assert(ret);
}

void* Thread::GetData( const LocalDataStorage& tls )
{
	return ::TlsGetValue(reinterpret_cast<DWORD>(tls));
}

void Thread::ThreadEntry( void* param )
{
	ThreadControlBlock* tcb = reinterpret_cast<ThreadControlBlock*>(param);
	assert(tcb != NULL);
	bool is_foreground = !tcb->IsBackground;

	LocalDataStorage slot = GlobalTLS::GetSlot(GlobalTLS::ThreadControlBlock);
	Thread::SetData(slot, &tcb);

	{
		AutoLock lock(*tcb);
		tcb->ID = Thread::ManagedThreadID();
		tcb->IsAlive = true;
        tcb->Handle = get_Handle();
	}

	if (is_foreground)
		Interlocked::Increment(foreground_thread_count_);

	try
	{
		tcb->ThreadStart();
	}
	catch (...)
	{
	}

	{
		AutoLock lock(*tcb);
		tcb->IsAlive = false;
		--tcb->ReferenceCount;
	}

	if (tcb->ReferenceCount == 0)
	{
		delete tcb;
		tcb = NULL;
	}

	if (is_foreground)
		Interlocked::Decrement(foreground_thread_count_);

    _endthread();
}

void Thread::Start()
{
	tcb_ = new ThreadControlBlock();
	tcb_->IsAlive = false;
	tcb_->IsBackground = false;
	tcb_->IsThreadPoolThread = false;
	tcb_->ReferenceCount = 2;
	tcb_->ThreadStart = thread_start_;
    tcb_->Handle = INVALID_VALUE;
	_beginthread(ThreadEntry, 0, tcb_);
}

void Thread::Sleep( unsigned int milliseconds )
{
	::Sleep(milliseconds);
}

bool Thread::IsAlive() const
{
	if (tcb_ == NULL)
		return false;
	return tcb_->IsAlive;
}

bool Thread::IsBackground() const
{
	assert(tcb_ != NULL);
	return tcb_->IsBackground;
}

bool Thread::IsThreadPoolThread() const
{
	assert(tcb_ != NULL);
	return tcb_->IsThreadPoolThread;
}

mUI::System::Threading::ThreadPriority Thread::Priority() const
{
	assert(tcb_ != NULL);
	return tcb_->Priority;
}

void Thread::Abort()
{
	if (tcb_ == NULL)
		return;

	AutoLock lock(*tcb_);
	if (tcb_->IsAlive)
	{
		HANDLE h = tcb_->Handle;
		assert(h != NULL && "Invalid Handle");
		bool tret = ::TerminateThread(h, -1) == TRUE;
		assert(tret && "TherminateThread failed!");

		--tcb_->ReferenceCount;
		if (!tcb_->IsBackground)
			Interlocked::Decrement(foreground_thread_count_);
	}
	else
	{
		return;
	}
}

void Thread::Join()
{
	Join(INFINITE);
}

bool Thread::Join( int miliseconds )
{
	if (tcb_ == NULL)
		return true;

	{
		AutoLock lock(*tcb_);
		if (!tcb_->IsAlive)
			return true;
	}

	HANDLE h = tcb_->Handle;
	assert(h != NULL && "Invalid Handle!");
	bool ret = WaitForSingleObject(h, miliseconds) == WAIT_OBJECT_0;

	return ret;
}

void Thread::SpinWait( int iterations )
{
	while (iterations > 0)
		--iterations;
}

Thread Thread::CurrentThread()
{
	LocalDataStorage slot = GlobalTLS::GetSlot(GlobalTLS::ThreadControlBlock);
	Thread thread;
	thread.tcb_ = reinterpret_cast<ThreadControlBlock*>(Thread::GetData(slot));
	if (thread.tcb_ == NULL)
	{
		_MakeTCB();
		thread.tcb_ = reinterpret_cast<ThreadControlBlock*>(Thread::GetData(slot));
	}
	assert(thread.tcb_ != NULL);
	AutoLock lock(thread.tcb_);
	++thread.tcb_->ReferenceCount;
	return thread;
}

void Thread::_MakeTCB()
{
	LocalDataStorage slot = GlobalTLS::GetSlot(GlobalTLS::ThreadControlBlock);
	ThreadControlBlock* tcb = new ThreadControlBlock();
	assert(tcb != NULL);
	assert(Thread::GetData(slot) == NULL);
	Thread::SetData(slot, tcb);

	IntPtr tid = Thread::ManagedThreadID();

	tcb->ReferenceCount = 1;
	tcb->ID = tid;
	tcb->IsAlive = true;
	tcb->IsBackground = false;
	tcb->IsThreadPoolThread = false;
	tcb->Handle = get_Handle();

	HANDLE h = tcb->Handle;
	int priority = ::GetThreadPriority(h);
	switch (priority)
	{
	case THREAD_PRIORITY_ABOVE_NORMAL:
		tcb->Priority = ThreadPriority::AboveNormal;
		break;

	case THREAD_PRIORITY_NORMAL:
		tcb->Priority = ThreadPriority::Normal;
		break;

	case THREAD_PRIORITY_BELOW_NORMAL:
		tcb->Priority = ThreadPriority::BelowNormal;
		break;

	default:
		{
			if (priority <= THREAD_PRIORITY_LOWEST)
				tcb->Priority = ThreadPriority::Lowest;
			else
				tcb->Priority = ThreadPriority::Highest;
		}
		break;
	}
}

void Thread::DisposeTCBForMainThread()
{
	LocalDataStorage slot = GlobalTLS::GetSlot(GlobalTLS::ThreadControlBlock);
	ThreadControlBlock* tcb = reinterpret_cast<ThreadControlBlock*>(Thread::GetData(slot));
	assert(tcb != NULL);
	delete tcb;
	Thread::SetData(slot, NULL);
}

void Thread::Dispose()
{
	if (tcb_ != NULL)
	{
		AutoLock lock(*tcb_);
		--tcb_->ReferenceCount;
		if (tcb_->ReferenceCount > 0)
			return;						// Still in use, don't delete.
		::CloseHandle(tcb_->Handle);
	}
	delete tcb_;
}

IntPtr Thread::get_Handle()
{
    IntPtr handle = INVALID_VALUE;
	bool ret = TRUE == ::DuplicateHandle(::GetCurrentProcess(), ::GetCurrentThread(), 
		::GetCurrentProcess(), reinterpret_cast<LPHANDLE>(&(handle)), THREAD_ALL_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
	assert(ret && "DuplicateHandle failed!");
    return handle;
}

}}}
