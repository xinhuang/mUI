#include "Lock.h"

namespace mUI{ namespace System{  namespace Threading{

Lock::Lock(void)
{
	::InitializeCriticalSection(&critical_section_);
}

Lock::~Lock(void)
{
	Release();
	::DeleteCriticalSection(&critical_section_);
}

void Lock::Acquire()
{
	::EnterCriticalSection(&critical_section_);
}

bool Lock::TryAcquire()
{
	return ::TryEnterCriticalSection(&critical_section_) == TRUE;
}

void Lock::Release()
{
	::LeaveCriticalSection(&critical_section_);
}

}}}
