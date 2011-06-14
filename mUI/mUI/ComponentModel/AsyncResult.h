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

#ifndef __ASYNCRESULT_H__
#define __ASYNCRESULT_H__

#include "../APC/IAsyncResult.h"
#include "../Threading/Threading.h"

namespace mUI{ namespace System{ 

class AsyncResult : public IAsyncResult
{
public:
	AsyncResult(void);
	virtual ~AsyncResult(void);

	virtual Threading::WaitHandle& AsyncWaitHandle()
	{
		return event_;
	}
	virtual bool IsComplete() const
	{
		return completed_;
	}

private:
	bool completed_;
	Threading::ManualResetEvent event_;
};

}}

#endif
