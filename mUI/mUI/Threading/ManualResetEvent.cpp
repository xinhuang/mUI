#include "ManualResetEvent.h"

namespace mUI{ namespace System{  namespace Threading{

ManualResetEvent::ManualResetEvent(void)
{
}

ManualResetEvent::~ManualResetEvent(void)
{
}

::HANDLE ManualResetEvent::CreateEvent( bool initial_state )
{
	return ::CreateEvent(NULL, TRUE, initial_state, NULL);
}

}}}
