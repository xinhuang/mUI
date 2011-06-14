#include "EventWaitHandle.h"

namespace mUI{ namespace System{  namespace Threading{

EventWaitHandle::EventWaitHandle(void)
{
}

EventWaitHandle::~EventWaitHandle(void)
{
}

::HANDLE EventWaitHandle::CreateEvent( bool initial_state )
{
	return WaitHandle::CreateEvent(initial_state);
}

}}}
