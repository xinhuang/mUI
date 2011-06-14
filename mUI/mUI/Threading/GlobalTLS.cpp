#include "GlobalTLS.h"

#include <cassert>

namespace mUI{ namespace System{  namespace Threading{

LocalDataStorage GlobalTLS::slot_[SLOT_MAX];

bool GlobalTLS::Init()
{
	bool ret = RegisterTLS();
	assert(ret);
	return true;
}

mUI::System::Threading::LocalDataStorage GlobalTLS::GetSlot( SLOT tr )
{
	assert(tr < SLOT_MAX);
	return slot_[tr];
}

bool GlobalTLS::RegisterTLS()
{
	for (size_t i = 0; i < SLOT_MAX; ++i)
	{
		slot_[i] = Thread::AllocateDataSlot();
		assert(slot_[i] != INVALID_LOCAL_DATA_STORAGE);
		Thread::SetData(slot_[i], NULL);
	}
	return true;
}

}}}
