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

#include "Export.h"
#include <System/System.h>

namespace mUI{ namespace System{ namespace ComponentModel{

class COMPONENTMODEL_ENTRY ISynchronizeInvoke
{
public:
	virtual ~ISynchronizeInvoke() {}

	virtual IAsyncResult* BeginInvoke(const Delegate<void>& method) = 0;
	virtual void EndInvoke(IAsyncResult& asyncResult) = 0;

	virtual void Invoke(const Delegate<>& method) = 0;

	virtual bool get_InvokeRequired() const = 0;
};

}}}

#endif
