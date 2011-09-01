#include "Lock.h"
#include <cassert>
#include <Windows.h>

#include "Thread.h"

namespace mUI{ namespace Pal{

typedef CRITICAL_SECTION LOCK;

PAL_ENTRY IntPtr NewLock()
{
	LOCK* lock = new LOCK();
	::InitializeCriticalSection(lock);
	return reinterpret_cast<IntPtr>(lock);
}

PAL_ENTRY void AcquireLock( IntPtr Lock )
{
	assert(Lock != NULL);
	LOCK* lock = reinterpret_cast<LOCK*>(Lock);
	::EnterCriticalSection(lock);
}

PAL_ENTRY bool TryAcquireLock( IntPtr Lock )
{
	assert(Lock != NULL);
	LOCK* lock = reinterpret_cast<LOCK*>(Lock);
	return ::TryEnterCriticalSection(lock) == TRUE;
}

PAL_ENTRY void ReleaseLock( IntPtr Lock )
{
	assert(Lock != NULL);
	LOCK* lock = reinterpret_cast<LOCK*>(Lock);
	::LeaveCriticalSection(lock);
}

PAL_ENTRY void DeleteLock( IntPtr Lock )
{
	assert(Lock != NULL);
	LOCK* lock = reinterpret_cast<LOCK*>(Lock);
	::DeleteCriticalSection(lock);
	delete Lock;
}

}}
