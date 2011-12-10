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

#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include "../Export.h"
#include "EventArgs.h"
#include "Delegate.h"

namespace mUI{ namespace System{

template<typename TEventArgs = EventArgs*>
class EventHandler : public Delegate<void, void*, TEventArgs>
{
public:
	EventHandler() {}
    virtual ~EventHandler() {}

	template<typename TClass, typename TClassF>
	EventHandler(TClass& c, void (TClassF::*f)(void*, TEventArgs))
	{
		Add(c, f);
	}
	template<typename TClass, typename TClassF>
	EventHandler(TClass* c, void (TClassF::*f)(void*, TEventArgs))
	{
		Add(*c, f);
	}
};

template
class SYSTEM_ENTRY EventHandler<EventArgs*>;

}}

#endif
