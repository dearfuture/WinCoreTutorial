#include<Windows.h>

#include<stdio.h>


HANDLE h1;
HANDLE h2;
CRITICAL_SECTION Section;
HANDLE hEvent=NULL;

DWORD WINAPI Thread1(PVOID)
{
	printf("ThreadId = %d\n",GetCurrentThreadId());
	//getchar();
	//WaitForSingleObject(hEvent,INFINITE);
	EnterCriticalSection(&Section);

	WaitForSingleObject(h2,INFINITE);

	LeaveCriticalSection(&Section);
	return 0;

}


DWORD WINAPI Thread2(PVOID)
{
	printf("ThreadId = %d\n",GetCurrentThreadId());
	
	EnterCriticalSection(&Section);

	WaitForSingleObject(h1,INFINITE);

	LeaveCriticalSection(&Section);
	return 0;
}


int main()
{
	/*
	while(1)
	{
		printf("ProcessId = %d\n",GetCurrentProcessId());
	}
	*/
	hEvent=CreateEvent(NULL,FALSE,FALSE,NULL);
	InitializeCriticalSection(&Section);
	printf("ProcessId = %d\n",GetCurrentProcessId());
	h1=CreateThread(NULL,0,Thread1,NULL,0,NULL);
	h2=CreateThread(NULL,0,Thread2,NULL,0,NULL);

	/*
	while(1)
	{
		printf("%d\n",GetCurrentThreadId());
		//Sleep(1000);
	}
	*/
	getchar();

	DeleteCriticalSection(&Section);
	
	return 0;

}