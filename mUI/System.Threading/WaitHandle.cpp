#include "WaitHandle.h"
#include <Pal.h>

#include <cassert>

namespace mUI{ namespace System{  namespace Threading{

WaitHandle::WaitHandle() : handle_(NULL)
{
}

WaitHandle::~WaitHandle()
{
}

void WaitHandle::WaitOne() const
{
	assert(handle_ != NULL);
	Pal::WaitForSingleObject(get_SafeWaitHandle(), INFINITE);
}

void WaitHandle::WaitAll( const vector<WaitHandle>& whs )
{
	if (whs.size() == 0)
		return;

	IntPtr* handles = new IntPtr[whs.size()];
	assert(handles != NULL);
	for (size_t i = 0; i < whs.size(); ++i)
	{
		handles[i] = whs[i].handle_;
	}

	Pal::WaitForMultipleObjects(whs.size(), handles, true, INFINITE);
	delete handles;
	handles = NULL;
}

void WaitHandle::WaitAny( const vector<WaitHandle>& whs )
{
	if (whs.size() == 0)
		return;

	IntPtr* handles = new IntPtr[whs.size()];
	assert(handles != NULL);
	for (size_t i = 0; i < whs.size(); ++i)
	{
		handles[i] = whs[i].handle_;
	}

	Pal::WaitForMultipleObjects(whs.size(), handles, false, INFINITE);
	delete handles;
	handles = NULL;
}

IntPtr WaitHandle::get_SafeWaitHandle() const
{
	return handle_;
}

void WaitHandle::set_SafeWaitHandle( IntPtr value )
{
	handle_ = value;
}

}}}
