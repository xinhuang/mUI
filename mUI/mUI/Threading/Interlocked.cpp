#include "Interlocked.h"

#include "../../stdafx.h"
#include <cassert>

namespace mUI{ namespace System{  namespace Threading{

int Interlocked::Increment( int& location )
{
	volatile LONG* p = reinterpret_cast<volatile LONG*>(&location);
	return ::InterlockedIncrement(p);
}

long long Interlocked::Increment( long long& location )
{
	assert(!"My Windows XP dont have the entry in kernel32.dll.");
	//return ::InterlockedIncrement64(&location);
	return 0;
}

IntPtr Interlocked::Increment( IntPtr& location )
{
	switch (sizeof(location))
	{
	case sizeof(int):
		{
			int* p = reinterpret_cast<int*>(&location);
			return reinterpret_cast<IntPtr>(Interlocked::Increment(*p));
		}
		break;

	case sizeof(long long):
		{
			long long* p = reinterpret_cast<long long*>(&location);
			return reinterpret_cast<IntPtr>(Interlocked::Increment(*p));
		}
		break;

	default:
		assert(!"Hello future man. I'm from the 2012. And the memory address range is 32-bit.");
	}
	return INVALID_VALUE;
}

int Interlocked::Decrement( int& location )
{
	volatile LONG* p = reinterpret_cast<volatile LONG*>(&location);
	return ::InterlockedDecrement(p);
}

long long Interlocked::Decrement( long long& location )
{
	assert(!"My Windows XP dont have the entry in kernel32.dll.");
	//return ::InterlockedDecrement64(&location);
	return 0;
}

IntPtr Interlocked::Decrement( IntPtr& location )
{
	switch (sizeof(location))
	{
	case sizeof(int):
		{
			int* p = reinterpret_cast<int*>(&location);
			return reinterpret_cast<IntPtr>(Interlocked::Decrement(*p));
		}
		break;

	case sizeof(long long):
		{
			long long* p = reinterpret_cast<long long*>(&location);
			return reinterpret_cast<IntPtr>(Interlocked::Decrement(*p));
		}
		break;

	default:
		assert(!"Hello future man. I'm from the 2012. And the memory address range is 32-bit.");
	}
	return INVALID_VALUE;
}

}}}
