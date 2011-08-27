#include "Lock.h"
#include <Pal.h>

namespace mUI{ namespace System{  namespace Threading{

Lock::Lock() : lock_(NULL)
{
	lock_ = Pal::CreateLock();
	assert(lock_ != NULL);
}

Lock::~Lock(void)
{
	Release();
	Pal::DestroyLock(lock_);
	lock_ = NULL;
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
