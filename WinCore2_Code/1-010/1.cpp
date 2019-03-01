#include<Windows.h>

#include<tchar.h>

#include<stdio.h>

DWORD Sum=0;

HANDLE hMutex=NULL;

/*
BOOL WINAPI SetConsoleCtrlHandler(
  __in_opt  PHANDLER_ROUTINE HandlerRoutine,
  __in      BOOL Add
);




*/


BOOL WINAPI HandlerRoutine(
  __in  DWORD dwCtrlType
)
{
	_tprintf(L"Exit Execute code\n");


	//可以写恢复共享资源的代码。
	WaitForSingleObject(hMutex,INFINITE);
	printf("我在处理后事\n");
	ReleaseMutex(hMutex);
	Sleep(5000);
	return 0;
}





DWORD WINAPI Thread(PVOID)
{
	_tprintf(L"EnTer\n");
	
	
	//EnterCriticalSection

	for(int i=0;i<100000;i++)
	{
		DWORD re = WaitForSingleObject(hMutex,INFINITE);
		_tprintf(L" re = %X\n",re);
		_tprintf(L"-------------------Thread =%X   i = %d Sum = %d\n",GetCurrentThreadId(),i,Sum);
		Sum++;
		ReleaseMutex(hMutex);
		Sleep(1000);
	}
	
	//LeaveCriticalSection
	return 0;
}

int k=0;
int Global_i=0;
DWORD WINAPI Thread2(PVOID)
{
	
	while(1)
	{
		//结束线程
		if(Global_i==1)
			break;
		WaitForSingleObject(hMutex,INFINITE);
		k++;//k++代表我们对共享资源的操作。
		_tprintf(L"abcddeeeffdd\n");
		Sleep(0);
		ReleaseMutex(hMutex);
		Sleep(1000);
		//结束线程
	}
	//LeaveCriticalSection
	return 0;
}






int _tmain()
{
	
	SetConsoleCtrlHandler(HandlerRoutine,TRUE);

	hMutex=CreateMutex(NULL,FALSE,NULL);

	HANDLE h=CreateThread(NULL,0,Thread2,NULL,0,NULL);

	_gettchar();

	//TerminateThread(h,0);
	Global_i=1;
	WaitForSingleObject(h,INFINITE);
	
	
	CreateThread(NULL,0,Thread,NULL,0,NULL);

	_gettchar();
	CloseHandle(hMutex);
	return 0;
}

