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

#ifndef __MUI_BASICTYPE_H__
#define __MUI_BASICTYPE_H__

#include <cmath>

namespace mUI{

// coz using intptr_t it would be impossible to reload foo(int) with foo(intptr_t). 
// (in my 32-bit machine, am i doing this right?)
typedef int* IntPtr;

const IntPtr INVALID_VALUE = reinterpret_cast<IntPtr>(-1);

#ifndef INFINITE
	const int INFINITE = -1;
#endif

#ifndef int64_t
	typedef long long int64_t;
#endif
#ifndef uint32_t
	typedef unsigned long long uint64_t;
#endif

#ifndef int32_t
	typedef int int32_t;
#endif
#ifndef uint32_t
	typedef unsigned int uint32_t;
#endif

#ifndef int16_t
	typedef short int16_t;
#endif
#ifndef uint16_t
	typedef unsigned short uint16_t;
#endif

#ifndef int8_t
	typedef char int8_t;
#endif
#ifndef uint8_t
	typedef unsigned char uint8_t;
#endif

typedef uint32_t utf32_t;

typedef uint32_t argb_t;

#ifndef NULL
#	define NULL (0)
#endif // NULL

#ifndef null
#	define null (0)
#endif // null

const float FLOAT_MIN = 0.0000001f;
const double DOUBLE_MIN = 0.000000000000001f;

inline bool fequ(const float lhs, const float rhs)
{
	return abs(lhs - rhs) < FLOAT_MIN;
}

inline bool fequ(const double lhs, const double rhs)
{
	return abs(lhs - rhs) < DOUBLE_MIN;
}

#ifdef _WINDOWS
#	ifndef DEPRECATED
#		define DEPRECATED __declspec(deprecated) 
#	endif // DEPRECATED
#endif 

}

#endif // __MUI_BASICTYPE_H__
