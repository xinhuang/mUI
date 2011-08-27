#include "Misc.h"

#include <Windows.h>

namespace mUI{ namespace Pal{

PAL_ENTRY void ReleaseBuffer( __in void* buffer )
{
	delete buffer;
}

PAL_ENTRY wchar_t* Utf8ToUtf16( __in const char* src )
{
	size_t cb_src = strlen(src);
	size_t need = ::MultiByteToWideChar(936, MB_PRECOMPOSED, src, cb_src, NULL, 0);
	wchar_t* dst = new wchar_t[need + 1];
	dst[need] = 0;
	::MultiByteToWideChar(936, MB_PRECOMPOSED, src, cb_src, dst, need + 1);
	return dst;
}

PAL_ENTRY char* Utf16ToAnsi( __in const wchar_t* src )
{
	size_t nsrc = wcslen(src);
	size_t need = ::WideCharToMultiByte(CP_UTF8, 0, src, nsrc, NULL, 0, NULL, NULL);
	char* dst = new char[need + 1];
	dst[need] = 0;
	::WideCharToMultiByte(CP_UTF8, 0, src, nsrc, dst, need + 1, NULL, NULL);
	return dst;
}

PAL_ENTRY void CloseHandle( __in IntPtr Handle )
{
	::CloseHandle(Handle);
}

}}
