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

#ifndef __INVOCATIONLIST_H__
#define __INVOCATIONLIST_H__

#include <map>
using std::map;
#include <deque>
using std::deque;

#include "../Threading/Threading.h"
using namespace mUI::System::Threading;

namespace mUI{ namespace System{ 

class ISynchronizeInvoke;

// TODO: Use SList instead of deque.
class InvocationList: private deque<ISynchronizeInvoke*>
{
public:
	InvocationList(void);
	~InvocationList(void);

	static void DoEvents();

	static void Register(ISynchronizeInvoke& invokable);
	static void Unregister(const ISynchronizeInvoke& invokable);

private:
	const IntPtr tid_;
	deque<ISynchronizeInvoke*> invokable_list_;
};

}}

#endif 
