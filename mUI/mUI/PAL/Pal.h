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

#ifndef __PAL_H__
#define __PAL_H__

// The platform abstraction layer

#if defined _WINDOWS
#	include "sal.h"
#else
#	define __in
#	define __out
#endif

namespace mUI{ namespace PAL{

	void ReleaseBuffer( __in void* buffer );

	wchar_t* Utf8ToUtf16( __in const char* src );
	char* Utf16ToAnsi( __in const wchar_t* src );

}}

#endif
