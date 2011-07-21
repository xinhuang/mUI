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

#ifndef __THREADING_INIT_H__
#define __THREADING_INIT_H__

#include "AutoLock.h"
#include "EventWaitHandle.h"
#include "Interlocked.h"
#include "Lock.h"
#include "Lockable.h"
#include "ManualResetEvent.h"
#include "Thread.h"
#include "ThreadPriority.h"
#include "WaitHandle.h"

#include "../System.h"

namespace mUI{ namespace System{ namespace Threading{

bool MUI_ENTRY Init();
void MUI_ENTRY Dispose();

}}}

#endif 
