#ifndef __MUIPAL_THREAD_H__
#define __MUIPAL_THREAD_H__

#include "Export.h"
#include "MuiSal.h"
#include "BasicType.h"

namespace mUI{ namespace Pal{

PAL_ENTRY IntPtr BeginThread( 
	__in void (*Entry)(void*),
	__in size_t StackSize,
	__in void* Args);

PAL_ENTRY void EndThread(
	);

PAL_ENTRY bool TerminateThread( 
	__in IntPtr Thread, 
	__in size_t ExitCode );

PAL_ENTRY IntPtr GetCurrentThreadId(
	);

// --------------------------------------------------------------------- //

PAL_ENTRY IntPtr	TlsAlloc(
	);

PAL_ENTRY bool	TlsFree(
	__in IntPtr TlsIndex);

PAL_ENTRY void*		TlsGetValue(
	__in IntPtr TlsIndex);

PAL_ENTRY bool		TlsSetValue(
	__in IntPtr TlsIndex, 
	__in void* Value);

}}

#endif // __MUIPAL_THREAD_H__
