#include<Windows.h>
#include<tchar.h>
/*
�ɵȴ�ʱ���ں˶���

���԰�����ں˶��󿴳�һ���ܹ���ʱ��ʱ��ʱ�ӡ���ʱ��ʱ���Ƶ�ʿ��������趨��

��ʼ����ʱ�Ӳ���ʱ�����ù���Ļ���ʹ��SetWaitableTimer,ֹͣʱ����CancelWaitableTimer,

����ʹ��ʱ�ӣ���ʱ�����٣�Ҳ�����ӵ��ĺ�����CloseHandle.



�ɵȴ�ʱ���ں˶�����غ�����
CancelWaitableTimer		��һ��ָ����ʱ���ں˶������õ�δ����״̬,�����Ὣ�Ѿ����źŵ�ʱ����λΪ���ź�״̬��
CreateWaitableTimer		�������ߴ�һ��ʱ���ں˶���.
CreateWaitableTimerEx	ͬ�ϣ�ֻ�����������ô򿪺���ʱ���ں˾�������е�Ȩ��.
OpenWaitableTimer		��һ���Ѿ����ڵ�ʱ���ں˶���.
SetWaitableTimer		����ָ����ʱ���ں˶���.
SetWaitableTimerEx		ͬ�ϣ�����ָ����ʱ���ں˶���.��Ŀǰû�з��������������ļ����������ô���MSDNֻ�Ǽ򵥵Ľ�����һ�£�
TimerAPCProc			ʱ���ں˶���APC����


BOOL WINAPI SetWaitableTimer(
  __in      HANDLE hTimer,
  __in      const LARGE_INTEGER *pDueTime,
  __in      LONG lPeriod,
  __in_opt  PTIMERAPCROUTINE pfnCompletionRoutine,
  __in_opt  LPVOID lpArgToCompletionRoutine,
  __in      BOOL fResume
);

hTimer:		ʱ���ں˶�������
pDueTime:	�೤ʱ���Ժ󣬸��ں˶����״α�Ϊ���ź�״̬��������ʾ����ʱ�䣬������ʾ���ʱ�䣨�Ӹú�����������һʱ�̿�ʼ����
lPeriod:	���ڣ���ʱ�ӱ�Ϊ���ź�״̬��೤ʱ���ڣ��ٴα�Ϊ���ź�״̬��
pfnCompletionRoutine:		APC��������
lpArgTocompletionRoutine:	���ݸ�APC���̵Ĳ���
fResume:	�����������TRUE��ʱ�����ϵͳ����ʡ��ģʽ�£����ʱ�ӱ�Ϊ���ź�״̬����ôϵͳ���ٴ���ʡ��ģʽ��ϵͳ�ָ��������FALSE����ôϵͳ��Ȼ����
			ʡ��ģʽ��

*/


/*

һ��Ҫ����ʱ�ӵļ���״̬�����ź�״̬��


Timers are initially inactive. To activate a timer, call SetWaitableTimer. If the timer is already active when you call SetWaitableTimer, the timer is stopped, then it is reactivated. Stopping the timer in this manner does not set the timer state to signaled, so threads blocked in a wait operation on the timer remain blocked. However, it does cancel any pending completion routines.
ʱ�����ʼ��״̬��δ����״̬�����Ե���SetWaitableTimer����������ʱ��������ʱ������Ѿ������ʱ�ٵ���SetWaitableTimer��������ô������ʱ��������ǰһ��SetWaitableTimer������APC���̣���ô������̻ᱻȡ����
When the specified due time arrives, the timer becomes inactive and the APC is queued to the thread that set the timer. The state of the timer is set to signaled, the timer is reactivated using the specified period, and the thread that set the timer calls the completion routine when it enters an alertable wait state. If the timer is set before the thread enters an alertable wait state, the APC is canceled. For more information, see QueueUserAPC.
��pDueTimeʱ�䵽���ʱ��ʱ�ӱ�Ϊ����״̬��APC��ע�뵽����setWaitabletimer�������߳��У�ʱ�ӵ�״̬������Ϊ���ź�״̬����ô���ʱ�ӻ������Ա��������������SetWaitableTimer���������õ����ڣ�������ʱ�ӱ���Ϊ���ź�״̬�������������̵Ļ���Ҳ��ע�뵽����SetWaitableTimer�������߳��С�������̵߳��ñ�ע����������ǰ����ʱ�ӵ���CancelWaitableTimer����SetWaitableTimer��������ô�Ѿ�ע���APC������̻ᱻȡ����
If the thread that set the timer terminates and there is an associated completion routine, the timer is canceled. However, the state of the timer remains unchanged. If there is no completion routine, then terminating the thread has no effect on the timer.
�������setWaitableTimer�������߳���ֹ����ô��ע�뵽���̵߳��������Ҳ�ᱻȡ������ʱ�ӵ�״̬����ı䣨�Ƿ����źţ��������ֹ���߳���û��ʱ����ص�������̣���ô�̵߳���ֹ��ʱ��û��Ӱ�졣
When a manual-reset timer is set to the signaled state, it remains in this state until SetWaitableTimer is called to reset the timer. As a result, a periodic manual-reset timer is set to the signaled state when the initial due time arrives and remains signaled until it is reset. When a synchronization timer is set to the signaled state, it remains in this state until a thread completes a wait operation on the timer object.
��һ���ֶ���λ��ʱ�ӱ����õ����ź�״̬������һֱ�������ź�״̬��ֱ���ٴε���SetWaitableTimer��������ʱ�ӡ�
If the system time is adjusted, the due time of any outstanding absolute timers is adjusted.
���ϵͳ���ı䣬��ô����ʱ�����֮������

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