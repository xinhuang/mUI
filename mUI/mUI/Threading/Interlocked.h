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

#ifndef __INTERLOCKED_H__
#define __INTERLOCKED_H__

#include "../System.h"

#include <cassert>

namespace mUI{ namespace System{  namespace Threading{

class MUI_ENTRY Interlocked
{
public:
	static int Increment(int& location);
	static int Increment(size_t& location) { return _PlatformIncrement(location); }
	static int64_t Increment(int64_t& location);
	static IntPtr Increment(IntPtr& location);

	static int Decrement(int& location);
	static int Decrement(size_t& location) { return _PlatformDecrement(location); }
	static int64_t Decrement(int64_t& location);
	static IntPtr Decrement(IntPtr& location);

	static int CompareExchange(int volatile* dest, int value, int comparand);
	static int64_t CompareExchange(int64_t volatile* dest, int64_t value, int64_t comparand);

private:
	template <typename T>
	static T _PlatformIncrement(T& location)
	{
		switch (sizeof(location))
		{
		case sizeof(int):
			{
				int* p = reinterpret_cast<int*>(&location);
				return static_cast<T>(Interlocked::Increment(*p));
			}

		case sizeof(long long):
			{
				long long* p = reinterpret_cast<long long*>(&location);
				return static_cast<T>(Interlocked::Increment(*p));
			}

		default:
			assert(!"Hello future man. I'm from the 2012. And the memory address range is 32-bit.");
		}
		return T();
	}
	template <typename T>
	static T _PlatformDecrement(T& location)
	{
		switch (sizeof(location))
		{
		case sizeof(int):
			{
				int* p = reinterpret_cast<int*>(&location);
				return static_cast<T>(Interlocked::Decrement(*p));
			}

		case sizeof(long long):
			{
				long long* p = reinterpret_cast<long long*>(&location);
				return static_cast<T>(Interlocked::Decrement(*p));
			}

		default:
			assert(!"Hello future man. I'm from the 2012. And the memory address range is 32-bit.");
		}
		return T();
	}
};

}}}

#endif
