#include "ManualResetEvent.h"
#include <Pal.h>

namespace mUI{ namespace System{  namespace Threading{

ManualResetEvent::ManualResetEvent(void)
{
	IntPtr handle = Pal::NewEvent(true, false, null);
	set_SafeWaitHandle(handle);
}

ManualResetEvent::~ManualResetEvent(void)
{
	Pal::DeleteEvent(get_SafeWaitHandle());
}

}}}
