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

#ifndef __IASYNCRESULT_H__
#define __IASYNCRESULT_H__

#include "../Threading/Threading.h"

#include "../../mUI.h"

namespace mUI{ namespace System{ 

namespace Threading{
	class WaitHandle;
}

class MUI_ENTRY IAsyncResult
{
public:
	virtual Threading::WaitHandle& getAsyncWaitHandle() = 0;
	virtual bool IsComplete() const = 0;
};

}}

#endif
