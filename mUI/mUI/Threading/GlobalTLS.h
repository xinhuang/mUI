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

#ifndef __GLOBALTLS_H__
#define __GLOBALTLS_H__

#include "../mUIBase.h"

#include "Thread.h"

namespace mUI{ namespace System{  namespace Threading{

class GlobalTLS
{
public:
	enum SLOT
	{
		ThreadControlBlock,

		SLOT_MAX
	};

	static bool Init();
	static LocalDataStoreSlot GetSlot(SLOT tr);

private:
	static bool RegisterTLS();

	static LocalDataStoreSlot slot_[SLOT_MAX];
};

}}}

#endif
