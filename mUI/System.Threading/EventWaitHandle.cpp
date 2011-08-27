#include "EventWaitHandle.h"
#include <Pal.h>

namespace mUI{ namespace System{  namespace Threading{

EventWaitHandle::EventWaitHandle(void)
{
	IntPtr handle = Pal::CreateEvent(false, false, NULL);
	set_SafeWaitHandle(handle);
}

EventWaitHandle::~EventWaitHandle(void)
{
	Pal::DestroyEvent(get_SafeWaitHandle());
	set_SafeWaitHandle(NULL);
}

void EventWaitHandle::Set() const
{
	Pal::SetEvent(get_SafeWaitHandle());
}

void EventWaitHandle::Reset() const
{
	Pal::ResetEvent(get_SafeWaitHandle());
}

}}}
