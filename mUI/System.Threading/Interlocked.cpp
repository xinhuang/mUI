#include "Interlocked.h"

#include <cassert>
#include <Windows.h>

namespace mUI{ namespace System{  namespace Threading{

int Interlocked::Increment( int& location )
{
	volatile LONG* p = reinterpret_cast<volatile LONG*>(&location);
	return ::InterlockedIncrement(p);
}

int64_t Interlocked::Increment( int64_t& location )
{
	assert(!"My Windows XP dont have the InterlockedIncrement64 in kernel32.dll.");
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

int64_t Interlocked::Decrement( int64_t& location )
{
	assert(!"My Windows XP dont have the InterlockedDecrement64 in kernel32.dll.");
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

int Interlocked::CompareExchange( int volatile* dest, int value, int comparand )
{
	LONG volatile* p = reinterpret_cast<LONG volatile*>(dest);
	return ::InterlockedCompareExchange(p, value, comparand);
}

int64_t Interlocked::CompareExchange( int64_t volatile* dest, int64_t value, int64_t comparand )
{
	LONGLONG volatile* p = reinterpret_cast<LONGLONG volatile*>(dest);
	assert(!"My Windows XP dont have the InterlockedCompareExchange64 in kernel32.dll.");
	//return ::InterlockedCompareExchange64(p, value, comparand);
	return 0;
}

}}}
