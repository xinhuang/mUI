#include "Lock.h"
#include <Pal.h>

namespace mUI{ namespace System{  namespace Threading{

Lock::Lock() : lock_(null)
{
	lock_ = Pal::NewLock();
	assert(lock_ != null);
}

Lock::~Lock(void)
{
	Release();
	Pal::DeleteLock(lock_);
	lock_ = null;
}

void Lock::Acquire()
{
	Pal::AcquireLock(lock_);
}

bool Lock::TryAcquire()
{
	return Pal::TryAcquireLock(lock_);
}

void Lock::Release()
{
	Pal::ReleaseLock(lock_);
}

}}}
