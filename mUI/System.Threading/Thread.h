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

#ifndef __THREAD_H__
#define __THREAD_H__

#include "Export.h"
#include <System/System.h>

#include "ThreadPriority.h"

namespace mUI{ namespace System{  namespace Forms{
	class Application;
}}}

namespace mUI{ namespace System{  namespace Threading{

typedef Delegate<void> ThreadStart;
typedef Delegate<void, void*> ParameterizedThreadStart;

typedef IntPtr LocalDataStoreSlot;
const LocalDataStoreSlot INVALID_LOCAL_DATA_STORAGE = reinterpret_cast<LocalDataStoreSlot>(-1);

class THREADING_ENTRY Thread
{
public:
	Thread() : _tcb(NULL) {}

	Thread(const Thread& thread);
	Thread& operator=(const Thread& thread);

	explicit Thread(const ThreadStart& thread_start);
	~Thread();

	bool IsAlive() const;
	bool IsBackground() const;
	bool IsThreadPoolThread() const;
	ThreadPriority Priority() const;
	// ThreadState ThreadState() const;

	void Start();
	void Start(void* param);
	void Abort();
	void Join();
	bool Join(int miliseconds);

	static void	Sleep(unsigned int milliseconds);
	static void SpinWait(int interations);

	static Thread	CurrentThread();
	static IntPtr	get_ManagedThreadID();

	static LocalDataStoreSlot AllocateDataSlot();
	static void* GetData(const LocalDataStoreSlot& slot);
	static void SetData(const LocalDataStoreSlot& slot, void* data);

	static void FreeDataSlot(const LocalDataStoreSlot& tls);			// Non-CLR

protected:
	friend bool THREADING_ENTRY Init();
	friend void THREADING_ENTRY Dispose();

	struct ThreadControlBlock;
	ThreadControlBlock* _tcb;

	static bool Init();
	static ThreadControlBlock* MakeTckForCurrentThread();

	static void DisposeTCBForMainThread();
	static void ThreadEntry(void* param);

	void Dispose();

private:
	ThreadStart _threadStart;

	static size_t _foregroundThreadCount;
	static LocalDataStoreSlot _tcbSlot;

	static IntPtr get_Handle();
};

}}}

#endif // __THREAD_H__
