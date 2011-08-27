#include "Event.h"

#include <Windows.h>

#undef CreateEvent

namespace mUI{ namespace Pal{

PAL_ENTRY IntPtr CreateEvent(
	__in bool ManualReset, 
	__in bool InitialValue, 
	__in const wchar_t* Name)
{
	return static_cast<IntPtr>(
		::CreateEventW(NULL, ManualReset, InitialValue, Name));
}

PAL_ENTRY void DestroyEvent( __in IntPtr Event )
{
	::CloseHandle(Event);
}

PAL_ENTRY bool SetEvent( __in IntPtr Event )
{
	return ::SetEvent(Event) == TRUE;
}

PAL_ENTRY bool ResetEvent( __in IntPtr Event )
{
	return ::ResetEvent(Event) == TRUE;	
}

PAL_ENTRY bool PulseEvent( __in IntPtr Event )
{
	return ::PulseEvent(Event) == TRUE;	
}

PAL_ENTRY bool WaitForSingleObject( __in IntPtr Handle, __in uint32_t Milliseconds )
{
	return ::WaitForSingleObject(Handle, Milliseconds) == TRUE;
}

PAL_ENTRY int WaitForMultipleObjects( __in uint32_t N, __in const IntPtr* Handles, __in bool WaitAll, __in uint32_t Milliseconds )
{
	const HANDLE* handles = reinterpret_cast<const HANDLE*>(Handles);
	return ::WaitForMultipleObjects(N, handles, WaitAll, Milliseconds);
}

}}
