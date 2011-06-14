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

#include "../Delegate/Delegate.h"

#include "../mUIBase.h"
#include "../../stdafx.h"

#include "ThreadPriority.h"

namespace mUI{ namespace System{  namespace Forms{
	class Application;
}}}

namespace mUI{ namespace System{  namespace Threading{

typedef Delegate<void> ThreadStart;
typedef Delegate<void, void*> ParameterizedThreadStart;

typedef IntPtr LocalDataStorage;
const LocalDataStorage INVALID_LOCAL_DATA_STORAGE = reinterpret_cast<LocalDataStorage>(TLS_OUT_OF_INDEXES);

class MUI_ENTRY Thread
{
public:
	Thread() : tcb_(NULL) {}

	Thread(const Thread& thread);
	Thread& operator=(const Thread& thread);

	Thread(const ThreadStart& thread_start);
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
	static IntPtr	ManagedThreadID();

	static LocalDataStorage AllocateDataSlot();
	static void* GetData(const LocalDataStorage& slot);
	static void SetData(const LocalDataStorage& slot, void* data);

	static void FreeDataSlot(const LocalDataStorage& tls);			// Non-CLR

protected:
	friend bool MUI_ENTRY Init();
	friend void MUI_ENTRY Dispose();

	static void _MakeTCB();

	static void DisposeTCBForMainThread();
	static void ThreadEntry(void* param);

	void Dispose();

private:
	ThreadStart thread_start_;

	struct ThreadControlBlock;
	ThreadControlBlock* tcb_;

	static size_t foreground_thread_count_;

	static IntPtr get_Handle();
};

}}}

#endif // __THREAD_H__
