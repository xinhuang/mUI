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

#ifndef __METHODINVOKER_H__
#define __METHODINVOKER_H__

#include "../Delegate/Delegate.h"
#include "ISynchronizeInvoke.h"
#include "../Threading/Threading.h"

#include <cassert>

namespace mUI{ namespace System{

class IAsyncResult;

class InvocationEntry
{
public:
	InvocationEntry(ISynchronizeInvoke& invokable, 
		const Delegate<void>& delegate, IAsyncResult** out_async_result)
		: invokable_(&invokable)
	{
		delegate_ = delegate;
		if (out_async_result != NULL)
		{
			assert(!"Not implemented!");
		}
		else
		{
			async_result_ = NULL;
		}
	}

	void Invoke()
	{
		delegate_();
		if (async_result_)
		{
			assert(!"Not implemented!");
		}
		else
		{
			// No need for existence.
			Dispose();
		}
	}
	void Dispose()
	{
		if (invokable_ != NULL)
		{
			invokable_ = NULL;
		}

		delete this;
	}

protected:
	virtual ~InvocationEntry()
	{
		if (async_result_ != NULL)
		{
			assert(!"Not implemented!");
		}
	}

private:

	ISynchronizeInvoke* invokable_;
	Delegate<void> delegate_;
	IAsyncResult* async_result_;
};

}}

#endif 
