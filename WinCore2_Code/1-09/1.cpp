#include<Windows.h>

#include<tchar.h>



/*
A mutex object is a synchronization object whose state is set to signaled when it is not owned by any thread, and nonsignaled when it is owned. Only one thread at a time can own a mutex object, whose name comes from the fact that it is useful in coordinating mutually exclusive access to a shared resource. For example, to prevent two threads from writing to shared memory at the same time, each thread waits for ownership of a mutex object before executing the code that accesses the memory. After writing to the shared memory, the thread releases the mutex object.
互斥对象只有在没有现成有用他的时候，互斥对象处于有信号状态。同一时刻，只能有一个现成拥有互斥对象，使用WaitForSingleObject/WaitForMultipleObjects函数获得互斥对象的所有权。也就是说，只有当互斥对象处于有信号状态的情况下，一个线程才能够获得互斥对象的所有权。


A thread uses the CreateMutex or CreateMutexEx function to create a mutex object. The creating thread can request immediate ownership of the mutex object and can also specify a name for the mutex object. It can also create an unnamed mutex. For additional information about names for mutex, event, semaphore, and timer objects, see Interprocess Synchronization.
互斥对象和关键区很像！

Threads in other processes can open a handle to an existing named mutex object by specifying its name in a call to the OpenMutex function. To pass a handle to an unnamed mutex to another process, use the DuplicateHandle function or parent-child handle inheritance.
使用互斥对象的名字，可以在不同进程间使用同一个互斥对象来同步线程。


Any thread with a handle to a mutex object can use one of the wait functions to request ownership of the mutex object. If the mutex object is owned by another thread, the wait function blocks the requesting thread until the owning thread releases the mutex object using the ReleaseMutex function. The return value of the wait function indicates whether the function returned for some reason other than the state of the mutex being set to signaled.


If more than one thread is waiting on a mutex, a waiting thread is selected. Do not assume a first-in, first-out (FIFO) order. External events such as kernel-mode APCs can change the wait order.

After a thread obtains ownership of a mutex, it can specify the same mutex in repeated calls to the wait-functions without blocking its execution. This prevents a thread from deadlocking itself while waiting for a mutex that it already owns. To release its ownership under such circumstances, the thread must call ReleaseMutex once for each time that the mutex satisfied the conditions of a wait function.
如果一个已经拥有互斥对象的线程，再次调用WaiFor函数来获得互斥对象的所有权，那么WaiFor函数立即返回，不会阻塞线程。但注意，必须要调用相同次数的RealseMutex函数来释放互斥对象的所有权。

If a thread terminates without releasing its ownership of a mutex object, the mutex object is considered to be abandoned. A waiting thread can acquire ownership of an abandoned mutex object, but the wait function will return WAIT_ABANDONED to indicate that the mutex object is abandoned. An abandoned mutex object indicates that an error has occurred and that any shared resource being protected by the mutex object is in an undefined state. If the thread proceeds as though the mutex object had not been abandoned, it is no longer considered abandoned after the thread releases its ownership. This restores normal behavior if a handle to the mutex object is subsequently specified in a wait function.
如果一个用户互斥对象所有权的线程退出，那么这个互斥对象此时处于abandoned状态。等待获取这个互斥对象所有权的线程（也就是被WaitFor函数阻塞的线程）中，WaitFor函数会立即返回，但返回值是：WAIT_ABANDONED/WAIT_ABANDONED_0.
Note that critical section objects provide synchronization similar to that provided by mutex objects, except that critical section objects can be used only by the threads of a single process.


CreateMutex;
ReleaseMutex;


HANDLE WINAPI CreateMutex(
  __in_opt  LPSECURITY_ATTRIBUTES lpMutexAttributes,
  __in      BOOL bInitialOwner,
  __in_opt  LPCTSTR lpName
);



1. 多次释放互斥对象的问题
2. abandoned问题

*/

DWORD Sum=0;

HANDLE hMutex=NULL;

DWORD WINAPI Thread(PVOID)
{
	DWORD re = WaitForSingleObject(hMutex,INFINITE);
	_tprintf(L" re = %X\n",re);
	//EnterCriticalSection
	for(int i=0;i<100000;i++)
	{
		_tprintf(L"-------------------Thread =%X   i = %d Sum = %d\n",GetCurrentThreadId(),i,Sum);
	}
	Sum++;
	ReleaseMutex(hMutex);
	//LeaveCriticalSection
	return 0;
}

int k=0;

DWORD WINAPI Thread2(PVOID)
{
	WaitForSingleObject(hMutex,INFINITE);
	//EnterCriticalSection
	__try
	{
		//MessageBox(NULL,L"abd",L"abd",NULL);
		
		{
			_tprintf(L"abcdef\n");
			return 0;
		}
		Sum++;
	}
	__finally
	{
		_tprintf(L"abc\n");
		ReleaseMutex(hMutex);
		
	}
	//LeaveCriticalSection
	return 0;
}






int _tmain()
{
	
	hMutex=CreateMutex(NULL,FALSE,NULL);

	HANDLE h=CreateThread(NULL,0,Thread2,NULL,0,NULL);

	_gettchar();

	TerminateThread(h,0);
	
	CreateThread(NULL,0,Thread,NULL,0,NULL);

	_gettchar();
	CloseHandle(hMutex);
	return 0;
}

