#ifndef __MUIPALMISC_H__
#define __MUIPALMISC_H__

#include "Export.h"
#include "MuiSal.h"
#include "BasicType.h"

namespace mUI{ namespace Pal{

PAL_ENTRY void ReleaseBuffer( __in void* buffer );

PAL_ENTRY wchar_t* Utf8ToUtf16( __in const char* src );
PAL_ENTRY char* Utf16ToAnsi( __in const wchar_t* src );

PAL_ENTRY void CloseHandle( __in IntPtr Handle );

}}

#endif // __MUIPALMISC_H__
