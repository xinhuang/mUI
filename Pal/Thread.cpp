#include "Thread.h"

#include <Windows.h>
#include <process.h>

namespace mUI{ namespace Pal{

PAL_ENTRY IntPtr TlsAlloc()
{
	return reinterpret_cast<IntPtr>(::TlsAlloc());
}

PAL_ENTRY bool TlsFree( __in IntPtr TlsIndex )
{
	return ::TlsFree(reinterpret_cast<DWORD>(TlsIndex)) == TRUE;
}

PAL_ENTRY void* TlsGetValue( __in IntPtr TlsIndex )
{
	return ::TlsGetValue(reinterpret_cast<DWORD>(TlsIndex));
}

PAL_ENTRY bool TlsSetValue( __in IntPtr TlsIndex, __in void* Value )
{
	return ::TlsSetValue(reinterpret_cast<DWORD>(TlsIndex), Value) == TRUE;
}

PAL_ENTRY IntPtr BeginThread( __in void (*Entry)(void*), __in size_t StackSize, __in void* Args )
{
	return reinterpret_cast<IntPtr>(::_beginthread(Entry, StackSize, Args));
}

PAL_ENTRY void EndThread()
{
	::_endthread();
}

PAL_ENTRY bool TerminateThread( __in IntPtr Thread, __in size_t ExitCode )
{
	return ::TerminateThread(Thread, ExitCode) == TRUE;
}

PAL_ENTRY IntPtr GetCurrentThreadId()
{
	return reinterpret_cast<IntPtr>(::GetCurrentThreadId());
}

}}
