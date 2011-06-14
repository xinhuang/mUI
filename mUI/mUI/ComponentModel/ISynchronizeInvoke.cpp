#include "ISynchronizeInvoke.h"

#include "InvocationEntry.h"
#include "InvocationList.h"

namespace mUI{ namespace System{ 

ISynchronizeInvoke::ISynchronizeInvoke() : tid_(Thread::ManagedThreadID())
{
	InvocationList::Register(*this);
}

ISynchronizeInvoke::~ISynchronizeInvoke()
{
	if (Thread::ManagedThreadID() != tid_)
	{
		assert(!"Instance created in another thread is destructing!");
	}
	while (!mi_list_.empty())
	{
		InvocationEntry* mi = mi_list_.back();
		mi->Dispose();
		mi_list_.pop_back();
	}

	InvocationList::Unregister(*this);
}

void ISynchronizeInvoke::BeginInvoke( const Delegate<void>& delegate)
{
	InvocationEntry* mi = new InvocationEntry(*this, delegate, NULL);
	Threading::AutoLock autolock(milist_lock_);
	mi_list_.push_back(mi);
}

void ISynchronizeInvoke::Remove( InvocationEntry& mi )
{
	Threading::AutoLock autolock(milist_lock_);
	for (deque<InvocationEntry*>::iterator iter = mi_list_.begin();
		iter != mi_list_.end(); ++iter)
	{
		if (*iter == &mi)
		{
			mi_list_.erase(iter);
			return;
		}
	}
}

void ISynchronizeInvoke::DoInvocations()
{
	Threading::AutoLock autolock(milist_lock_);
	for (size_t n = mi_list_.size(); n > 0; --n)
	{
		InvocationEntry* mi = mi_list_.front();
		assert(mi != NULL);

		mi_list_.pop_front();
		mi->Invoke();
	}
}

bool ISynchronizeInvoke::InvokeRequired() const
{
	return Threading::Thread::ManagedThreadID() != tid_;
}

}}
