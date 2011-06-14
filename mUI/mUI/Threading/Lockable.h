﻿/*
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

#ifndef __LOCKABLE_H__
#define __LOCKABLE_H__

#include "Lock.h"

#include "../mUIBase.h"

namespace mUI{ namespace System{  namespace Threading{

class MUI_ENTRY Lockable
{
public:

	Lock& GetLock()
	{
		return lock_;
	}

private:
	Lock lock_;
};

}}}

#endif
