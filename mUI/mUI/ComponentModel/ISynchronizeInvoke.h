/*
	Copyright 2011 hello.patz@gmail.com

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#ifndef __ISYNCHRONIZEINVOKE_H__
#define __ISYNCHRONIZEINVOKE_H__

#include "../Delegate/Delegate.h"
#include "../Threading/Threading.h"

#include "../mUIBase.h"

#include <deque>
using std::deque;

namespace mUI{ namespace System{ 

class IAsyncResult;
class InvocationEntry;

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif

class MUI_ENTRY ISynchronizeInvoke
{
public:
	ISynchronizeInvoke();
	virtual ~ISynchronizeInvoke();

	//IAsyncResult* BeginInvoke(const Delegate<void>& delegate);
	//void* EndInvoke(IAsyncResult& asyncResult);

	void BeginInvoke(const Delegate<void>& delegate);

	bool InvokeRequired() const;

private:
	void Remove(InvocationEntry& mi);

	friend class InvocationList;
	void DoInvocations();

private:
	Threading::Lock milist_lock_;
	deque<InvocationEntry*> mi_list_;
	const IntPtr tid_;
};

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

}}

#endif
