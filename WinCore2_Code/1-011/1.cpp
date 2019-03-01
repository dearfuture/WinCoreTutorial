#include<Windows.h>
#include<tchar.h>
/*
CreateSemaphore
OpenSemaphore
ReleaseSemaphore
WaitForSingleObject
WaitForMultipleObjects

信号灯可以认为是一个能够记住通行车辆个数的红绿灯，当绿灯（有信号）时，车辆（等待信号灯的线程）可以同行，无信号时，车辆（等待信号灯的线程）不可以同行。

使用CreateSemaphore函数创建信号灯。
使用ReleaseSemaphore函数来增加信号灯中允许运行的线程个数。
WaiForSingleObject和WaiForMultipleObjects函数每等待成功一次，减少一个信号灯的同行个数。






*/
long Sum=0;
HANDLE hSemaphore=NULL;

DWORD WINAPI Thread(PVOID)
{
	LONG Pre_Count=0;
	DWORD re = WaitForSingleObject(hSemaphore,INFINITE);
	InterlockedIncrement(&Sum);
	if(re==WAIT_OBJECT_0)
	{
		for(int i=0;i<10;i++)
		{
			_tprintf(L"Sum = %d\n",Sum);
			Sleep(100);
		}
		InterlockedDecrement(&Sum);
		ReleaseSemaphore(hSemaphore,1,&Pre_Count);
	}

	return 0;
}




int _tmain()
{
	long count;
	hSemaphore=CreateSemaphore(NULL,3,4,NULL);

	BOOL re =ReleaseSemaphore(hSemaphore,1,&count);


	for(int i=0;i<100;i++)
	{
		CreateThread(NULL,0,Thread,NULL,0,NULL);
	}
	/*
	while(1)
	{
		ReleaseSemaphore(hSemaphore,1,NULL);
	}
	*/
	_gettchar();

	return 0;
}