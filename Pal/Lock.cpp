#include "Lock.h"
#include <cassert>
#include <Windows.h>

#include "Thread.h"

namespace mUI{ namespace Pal{

typedef CRITICAL_SECTION LOCK;

PAL_ENTRY IntPtr CreateLock()
{
	CRITICAL_SECTION* lock = new CRITICAL_SECTION();
	::InitializeCriticalSection(lock);
	return reinterpret_cast<IntPtr>(lock);
}

PAL_ENTRY void AcquireLock( IntPtr Lock )
{
	assert(Lock != NULL);
	CRITICAL_SECTION* lock = reinterpret_cast<CRITICAL_SECTION*>(Lock);
	::EnterCriticalSection(lock);
}

PAL_ENTRY bool TryAcquireLock( IntPtr Lock )
{
	assert(Lock != NULL);
	CRITICAL_SECTION* lock = reinterpret_cast<CRITICAL_SECTION*>(Lock);
	return ::TryEnterCriticalSection(lock) == TRUE;
}

PAL_ENTRY void ReleaseLock( IntPtr Lock )
{
	assert(Lock != NULL);
	CRITICAL_SECTION* lock = reinterpret_cast<CRITICAL_SECTION*>(Lock);
	::LeaveCriticalSection(lock);
}

PAL_ENTRY void DestroyLock( IntPtr Lock )
{
	assert(Lock != NULL);
	CRITICAL_SECTION* lock = reinterpret_cast<CRITICAL_SECTION*>(Lock);
	::DeleteCriticalSection(lock);
}

}}
