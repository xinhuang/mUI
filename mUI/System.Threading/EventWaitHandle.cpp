#include "EventWaitHandle.h"
#include <Pal.h>

namespace mUI{ namespace System{  namespace Threading{

EventWaitHandle::EventWaitHandle(void)
{
	IntPtr handle = Pal::NewEvent(false, false, NULL);
	set_SafeWaitHandle(handle);
}

EventWaitHandle::~EventWaitHandle(void)
{
	Pal::DeleteEvent(get_SafeWaitHandle());
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
