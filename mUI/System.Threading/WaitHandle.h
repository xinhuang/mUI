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

#ifndef __WAITHANDLE_H__
#define __WAITHANDLE_H__

#include "Export.h"

#include <vector>
using std::vector;

#include <System/System.h>

namespace mUI{ namespace System{  namespace Threading{

class THREADING_ENTRY WaitHandle
{
public:
	WaitHandle();
	virtual ~WaitHandle();

	virtual void WaitOne() const;

	IntPtr get_SafeWaitHandle() const;
	void set_SafeWaitHandle(IntPtr value);

	static void WaitAll(const vector<WaitHandle>& whs);
	static void WaitAny(const vector<WaitHandle>& whs);

private:
	IntPtr handle_;
};

}}}

#endif 
