#ifndef __MUIPALEVENT_H__
#define __MUIPALEVENT_H__

#include "Export.h"
#include "BasicType.h"

namespace mUI{ namespace Pal{

PAL_ENTRY IntPtr NewEvent(
	__in bool ManualReset, 
	__in bool InitialValue, 
	__in const wchar_t* Name);

PAL_ENTRY void DeleteEvent( __in IntPtr Event);

PAL_ENTRY bool SetEvent(
	__in IntPtr Event);

PAL_ENTRY bool ResetEvent(
	__in IntPtr Event);

PAL_ENTRY bool PulseEvent(
	__in IntPtr Event);

PAL_ENTRY bool WaitForSingleObject( 
	__in IntPtr Handle, 
	__in uint32_t Milliseconds );

PAL_ENTRY int WaitForMultipleObjects(
	__in uint32_t N, 
	__in const IntPtr* Handles,
	__in bool WaitAll,
	__in uint32_t Milliseconds);

}}

#endif // __MUIPALEVENT_H__
