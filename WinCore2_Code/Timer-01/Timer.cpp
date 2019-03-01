#include<Windows.h>
#include<tchar.h>
/*
可等待时钟内核对象。

可以把这个内核对象看成一个能够定时报时的时钟。报时的时间和频率可以自由设定。

开始启动时钟并给时钟设置规则的话，使用SetWaitableTimer,停止时钟用CancelWaitableTimer,

不再使用时钟，将时钟销毁，也就是扔掉的函数是CloseHandle.



可等待时间内核对象相关函数：
CancelWaitableTimer		将一个指定的时间内核对象设置到未激活状态,但不会将已经有信号的时钟置位为无信号状态。
CreateWaitableTimer		创建或者打开一个时间内核对象.
CreateWaitableTimerEx	同上，只不过可以设置打开后获得时间内核句柄所具有的权限.
OpenWaitableTimer		打开一个已经存在的时间内核对象.
SetWaitableTimer		激活指定的时间内核对象.
SetWaitableTimerEx		同上，激活指定的时间内核对象.（目前没有发现这个函数多余的几个参数的用处，MSDN只是简单的介绍了一下）
TimerAPCProc			时间内核对象APC例程


BOOL WINAPI SetWaitableTimer(
  __in      HANDLE hTimer,
  __in      const LARGE_INTEGER *pDueTime,
  __in      LONG lPeriod,
  __in_opt  PTIMERAPCROUTINE pfnCompletionRoutine,
  __in_opt  LPVOID lpArgToCompletionRoutine,
  __in      BOOL fResume
);

hTimer:		时间内核对象句柄；
pDueTime:	多长时间以后，该内核对象首次变为有信号状态，正数表示绝对时间，负数表示相对时间（从该函数被调用那一时刻开始）。
lPeriod:	周期，在时钟变为有信号状态后多长时间内，再次变为有信号状态。
pfnCompletionRoutine:		APC调用例程
lpArgTocompletionRoutine:	传递给APC例程的参数
fResume:	当这个参数是TRUE的时候，如果系统处于省电模式下，这个时钟变为有信号状态，那么系统不再处于省点模式，系统恢复。如果是FALSE，那么系统仍然处于
			省电模式。

*/


/*

一定要区分时钟的激活状态和有信号状态。


Timers are initially inactive. To activate a timer, call SetWaitableTimer. If the timer is already active when you call SetWaitableTimer, the timer is stopped, then it is reactivated. Stopping the timer in this manner does not set the timer state to signaled, so threads blocked in a wait operation on the timer remain blocked. However, it does cancel any pending completion routines.
时间对象开始的状态是未激活状态，可以调用SetWaitableTimer函数来激活时间对象。如果时间对象已经激活，此时再调用SetWaitableTimer函数，那么会重置时间对象，如果前一个SetWaitableTimer设置了APC例程，那么这个例程会被取消。
When the specified due time arrives, the timer becomes inactive and the APC is queued to the thread that set the timer. The state of the timer is set to signaled, the timer is reactivated using the specified period, and the thread that set the timer calls the completion routine when it enters an alertable wait state. If the timer is set before the thread enters an alertable wait state, the APC is canceled. For more information, see QueueUserAPC.
当pDueTime时间到达的时候，时钟变为激活状态，APC被注入到调用setWaitabletimer函数的线程中，时钟的状态被设置为有信号状态。那么随后，时钟会周期性被激活（激活周期是SetWaitableTimer函数中设置的周期），并且时钟被置为有信号状态，如果有完成例程的话，也被注入到调用SetWaitableTimer函数的线程中。如果在线程调用被注入的完成例程前，对时钟调用CancelWaitableTimer或者SetWaitableTimer函数，那么已经注入的APC完成例程会被取消。
If the thread that set the timer terminates and there is an associated completion routine, the timer is canceled. However, the state of the timer remains unchanged. If there is no completion routine, then terminating the thread has no effect on the timer.
如果调用setWaitableTimer函数的线程终止，那么被注入到该线程的完成例程也会被取消。但时钟的状态不会改变（是否有信号）。如果终止的线程中没有时钟相关的完成例程，那么线程的终止对时钟没有影响。
When a manual-reset timer is set to the signaled state, it remains in this state until SetWaitableTimer is called to reset the timer. As a result, a periodic manual-reset timer is set to the signaled state when the initial due time arrives and remains signaled until it is reset. When a synchronization timer is set to the signaled state, it remains in this state until a thread completes a wait operation on the timer object.
当一个手动置位的时钟被设置到有信号状态，他会一直保持有信号状态，直到再次调用SetWaitableTimer函数重置时钟。
If the system time is adjusted, the due time of any outstanding absolute timers is adjusted.
如果系统被改变，那么绝对时间会随之调整。

If the thread that called SetWaitableTimer exits, the timer is canceled. This stops the timer before it can be set to the signaled state and cancels outstanding APCs; it does not change the signaled state of the timer.

*/

HANDLE hTimer=NULL;


DWORD WINAPI Thread(PVOID)
{
	static int i=0;
	while(1)
	{
		WaitForSingleObject(hTimer,INFINITE);
		_tprintf(L"wait ok %d\n",i);
		i++;
		Sleep(100);
	}

	return 0;
}

VOID CALLBACK TimerAPCProc(
   LPVOID lpArg,               // Data value
   DWORD dwTimerLowValue,      // Timer low value
   DWORD dwTimerHighValue )    // Timer high value

{
 
   static int i=0;
   _tprintf(L"My Apc %d\n",i);
   //_tprintf(L"id = %d\n",GetCurrentThreadId());
   i++;

}

DWORD WINAPI Thread1(PVOID)
{
	_tprintf(L"id = %d\n",GetCurrentThreadId());
	LARGE_INTEGER Large_Integer={0};
	Large_Integer.QuadPart=-10000000*1;
	hTimer=CreateWaitableTimer(NULL,TRUE,NULL);
	SetWaitableTimer(hTimer,&Large_Integer,1000,TimerAPCProc,NULL,FALSE);
	
	//CreateThread(NULL,0,Thread,NULL,0,NULL);
	while(1)
	{
		SleepEx(INFINITE,TRUE);
		//Sleep(2000);
		//_tprintf(L"cancel\n");
		//CancelWaitableTimer(hTimer);
		//SetWaitableTimer(hTimer,&Large_Integer,1000,NULL,NULL,FALSE);
	}

	return 0;
}



int _tmain()
{
	/*
	_tprintf(L"id = %d\n",GetCurrentThreadId());
	LARGE_INTEGER Large_Integer={0};
	Large_Integer.QuadPart=-10000000*1;
	hTimer=CreateWaitableTimer(NULL,TRUE,NULL);
	SetWaitableTimer(hTimer,&Large_Integer,1000,TimerAPCProc,NULL,FALSE);
	
	//CreateThread(NULL,0,Thread,NULL,0,NULL);
	while(1)
	{
		SleepEx(INFINITE,TRUE);
		//Sleep(2000);
		//_tprintf(L"cancel\n");
		//CancelWaitableTimer(hTimer);
	}
	*/
	HANDLE h = CreateThread(NULL,0,Thread1,NULL,0,NULL);
	CreateThread(NULL,0,Thread,NULL,0,NULL);
	Sleep(5000);
	//TerminateThread(h,0);
	CancelWaitableTimer(hTimer);
	_gettchar();
	return 0;
}