#include "InvocationList.h"

#include "../Threading/AutoLock.h"
#include "../Threading/GlobalTLS.h"
#include "InvocationEntry.h"

#include <cassert>

namespace mUI{ namespace System{

using namespace Threading;

InvocationList::InvocationList(void) : tid_(Thread::ManagedThreadID())
{
	Thread::SetData(Threading::GlobalTLS::GetSlot(Threading::GlobalTLS::InvocableObject), this);
}

InvocationList::~InvocationList(void)
{
	assert(empty());
}

void InvocationList::DoEvents()
{
	LocalDataStorage slot = Threading::GlobalTLS::GetSlot(Threading::GlobalTLS::InvocableObject);
	InvocationList* il = reinterpret_cast<InvocationList*>(Thread::GetData(slot));
	if (il != NULL)
	{
		for (size_t i = 0; i < il->size(); ++i)
		{
			ISynchronizeInvoke* invokable = (*il)[i];
			assert(invokable != NULL);
			invokable->DoInvocations();
		}
	}
}

void InvocationList::Register( ISynchronizeInvoke& invokable )
{
	InvocationList* il = NULL;
	LocalDataStorage slot = Threading::GlobalTLS::GetSlot(Threading::GlobalTLS::InvocableObject);

	il = reinterpret_cast<InvocationList*>(Thread::GetData(slot));
	if (il == NULL)
	{
		il = new InvocationList();
		Thread::SetData(slot, il);
	}

	assert(il != NULL);
	il->push_back(&invokable);
}

void InvocationList::Unregister( const ISynchronizeInvoke& invokable )
{
	LocalDataStorage slot = Threading::GlobalTLS::GetSlot(Threading::GlobalTLS::InvocableObject);
	InvocationList* il = reinterpret_cast<InvocationList*>(Thread::GetData(slot));
	assert(il != NULL);

	for (iterator iter = il->begin(); iter != il->end(); ++iter)
	{
		assert(*iter != NULL);
		if (*iter == &invokable)
		{
			il->erase(iter);
			break;
		}
	}

	if (il->empty())
	{
		delete il;
		Thread::SetData(slot, NULL);
	}
}

}}
