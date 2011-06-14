#include "WaitHandle.h"

#include <cassert>

namespace mUI{ namespace System{  namespace Threading{

WaitHandle::WaitHandle()
{
	handle_ = CreateEvent(FALSE);
	assert(handle_ != NULL);
}

WaitHandle::~WaitHandle()
{
	::CloseHandle(handle_);
	handle_ = NULL;
}

void WaitHandle::WaitOne() const
{
	assert(handle_ != NULL);
	::WaitForSingleObject(handle_, INFINITE);
}

void WaitHandle::WaitAll( const vector<WaitHandle>& whs )
{
	if (whs.size() == 0)
		return;

	HANDLE* handles = new HANDLE[whs.size()];
	assert(handles != NULL);
	for (size_t i = 0; i < whs.size(); ++i)
	{
		handles[i] = whs[i].handle_;
	}

	::WaitForMultipleObjects(whs.size(), handles, TRUE, INFINITE);
	delete handles;
	handles = NULL;
}

void WaitHandle::WaitAny( const vector<WaitHandle>& whs )
{
	if (whs.size() == 0)
		return;

	HANDLE* handles = new HANDLE[whs.size()];
	assert(handles != NULL);
	for (size_t i = 0; i < whs.size(); ++i)
	{
		handles[i] = whs[i].handle_;
	}

	::WaitForMultipleObjects(whs.size(), handles, FALSE, INFINITE);
	delete handles;
	handles = NULL;
}

::HANDLE WaitHandle::CreateEvent( bool initial_state )
{
	return ::CreateEventW(NULL, FALSE, initial_state, NULL);
}

}}}
