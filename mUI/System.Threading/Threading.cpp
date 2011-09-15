#include "Threading.h"

namespace mUI{ namespace System{ namespace Threading{

bool Init()
{
	//bool ret = GlobalTLS::Init();
	bool ret = Thread::Init();
	assert(ret);

	return ret;
}

void THREADING_ENTRY Dispose()
{
	Thread::DisposeTCBForMainThread();
}

}}}