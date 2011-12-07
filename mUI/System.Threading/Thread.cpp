#include "Thread.h"

#include "AutoLock.h"
#include "Interlocked.h"

#include <Pal.h>

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

	static ThreadControlBlock* Release( ThreadControlBlock* tcb ) 
	{
		{
			AutoLock lock(*tcb);
			--tcb->ReferenceCount;
		}

		if (tcb->ReferenceCount == 0)
		{
			delete tcb;
			tcb = NULL;
		}
		return tcb;
	}
};

// ------------------------------------------------------- //

size_t Thread::_foregroundThreadCount = 0;		// Using Interlocked method to access
LocalDataStoreSlot Thread::_tcbSlot = INVALID_LOCAL_DATA_STORAGE;

Thread::Thread( const ThreadStart& thread_start ) : _tcb(NULL)
{
	_threadStart = thread_start;
}

Thread::Thread( const Thread& thread )
{
	*this = thread;
}

Thread& Thread::operator=( const Thread& thread )
{
	this->Dispose();

	if (thread._tcb != NULL)
	{
		AutoLock lock(*thread._tcb);
		this->_tcb = thread._tcb;
		++this->_tcb->ReferenceCount;
	}
	this->_threadStart = thread._threadStart;

	return *this;
}

Thread::~Thread()
{
	Dispose();
}

IntPtr Thread::get_ManagedThreadID()
{
	return reinterpret_cast<IntPtr>(::GetCurrentThreadId());
}

LocalDataStoreSlot Thread::AllocateDataSlot()
{
	return Pal::TlsAlloc();
}

void Thread::FreeDataSlot( const LocalDataStoreSlot& tls )
{
	bool ret = Pal::TlsFree(tls);
	assert(ret);
}

void Thread::SetData( const LocalDataStoreSlot& tls, void* value )
{
	bool ret = Pal::TlsSetValue(tls, value);
	assert(ret);
}

void* Thread::GetData( const LocalDataStoreSlot& tls )
{
	return Pal::TlsGetValue(tls);
}

void Thread::ThreadEntry( void* param )
{
	ThreadControlBlock* tcb = reinterpret_cast<ThreadControlBlock*>(param);
	assert(tcb != NULL);
	bool isForeground = !tcb->IsBackground;

	LocalDataStoreSlot slot = _tcbSlot;
	Thread::SetData(slot, &tcb);

	{
		AutoLock lock(*tcb);
		tcb->ID = Thread::get_ManagedThreadID();
		tcb->IsAlive = true;
        tcb->Handle = get_Handle();
	}

	if (isForeground)
		Interlocked::Increment(_foregroundThreadCount);

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

	if (isForeground)
		Interlocked::Decrement(_foregroundThreadCount);

	Pal::EndThread();
}

void Thread::Start()
{
	_tcb = new ThreadControlBlock();
	_tcb->IsAlive = false;
	_tcb->IsBackground = false;
	_tcb->IsThreadPoolThread = false;
	_tcb->ReferenceCount = 2;
	_tcb->ThreadStart = _threadStart;
    _tcb->Handle = INVALID_VALUE;
	Pal::BeginThread(ThreadEntry, 0, _tcb);
}

void Thread::Sleep( unsigned int milliseconds )
{
	::Sleep(milliseconds);
}

bool Thread::IsAlive() const
{
	if (_tcb == NULL)
		return false;
	return _tcb->IsAlive;
}

bool Thread::IsBackground() const
{
	assert(_tcb != NULL);
	return _tcb->IsBackground;
}

bool Thread::IsThreadPoolThread() const
{
	assert(_tcb != NULL);
	return _tcb->IsThreadPoolThread;
}

ThreadPriority Thread::Priority() const
{
	assert(_tcb != NULL);
	return _tcb->Priority;
}

void Thread::Abort()
{
	if (_tcb == NULL)
		return;

	AutoLock lock(*_tcb);
	if (_tcb->IsAlive)
	{
		IntPtr h = _tcb->Handle;
		assert(h != NULL && "Invalid Handle");
		bool tret = Pal::TerminateThread(h, -1) == TRUE;
		assert(tret && "TherminateThread failed!");

		if (!_tcb->IsBackground)
			Interlocked::Decrement(_foregroundThreadCount);
		delete _tcb;
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
	if (_tcb == NULL)
		return true;

	{
		AutoLock lock(*_tcb);
		if (!_tcb->IsAlive)
			return true;
	}

	HANDLE h = _tcb->Handle;
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
	LocalDataStoreSlot slot = _tcbSlot;
	Thread thread;
	thread._tcb = reinterpret_cast<ThreadControlBlock*>(Thread::GetData(slot));
	if (thread._tcb == NULL)
		thread._tcb = MakeTckForCurrentThread();
	
	assert(thread._tcb != NULL);
	AutoLock lock(thread._tcb);
	++thread._tcb->ReferenceCount;
	return thread;
}

Thread::ThreadControlBlock* Thread::MakeTckForCurrentThread()
{
	LocalDataStoreSlot slot = _tcbSlot;
	ThreadControlBlock* tcb = new ThreadControlBlock();
	assert(tcb != NULL);
	assert(Thread::GetData(slot) == NULL);
	Thread::SetData(slot, tcb);

	IntPtr tid = Thread::get_ManagedThreadID();

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

	return tcb;
}

void Thread::DisposeTCBForMainThread()
{
	LocalDataStoreSlot slot = _tcbSlot;
	ThreadControlBlock* tcb = reinterpret_cast<ThreadControlBlock*>(Thread::GetData(slot));
	assert(tcb != NULL);
	delete tcb;
	Thread::SetData(slot, NULL);
}

void Thread::Dispose()
{
	if (_tcb != NULL)
	{
		AutoLock lock(*_tcb);
		--_tcb->ReferenceCount;
		if (_tcb->ReferenceCount > 0)
			return;						// Still in use, don't delete.
		::CloseHandle(_tcb->Handle);
	}
	delete _tcb;
}

IntPtr Thread::get_Handle()
{
    IntPtr handle = INVALID_VALUE;
	bool ret = TRUE == ::DuplicateHandle(::GetCurrentProcess(), ::GetCurrentThread(), 
		::GetCurrentProcess(), reinterpret_cast<LPHANDLE>(&(handle)), THREAD_ALL_ACCESS, FALSE, DUPLICATE_SAME_ACCESS);
	assert(ret && "DuplicateHandle failed!");
    return handle;
}

bool Thread::Init()
{
	_tcbSlot = Thread::AllocateDataSlot();
	assert(_tcbSlot != INVALID_LOCAL_DATA_STORAGE);
	Thread::MakeTckForCurrentThread();
	return true;
}

}}}
