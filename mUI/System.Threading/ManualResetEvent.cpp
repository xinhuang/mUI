#include "ManualResetEvent.h"
#include <Pal.h>

namespace mUI{ namespace System{  namespace Threading{

ManualResetEvent::ManualResetEvent(void)
{
	IntPtr handle = Pal::CreateEvent(true, false, NULL);
	set_SafeWaitHandle(handle);
}

ManualResetEvent::~ManualResetEvent(void)
{
	Pal::DestroyEvent(get_SafeWaitHandle());
}

}}}
