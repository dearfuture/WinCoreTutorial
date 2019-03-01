/*
内核同步对象

1. 进程1创建一个文件，给文件中写入数据，那么进程2，在进程1创建完这个文件并写入数据后，进程2在读取这个文件中的内容。

事件内核对象。

1.1 创建打开内核对象hEvent；
1.2 创建文件，写入数据；
1.3 将内核对象hEvent设置到有信号状态。



2.1 创建打开内核对象hEvent；
2.2 等待内核对象有信号；
2.3 打开文件，读取数据。

WaitForSingleObject

*/


#include<Windows.h>
#include<tchar.h>
long i=0;
DWORD* pBlock=NULL;

DWORD WINAPI Thread1(PVOID p)
{
	_gettchar();
	HANDLE h=(HANDLE)p;
	pBlock=(DWORD*)HeapAlloc(GetProcessHeap(),0,sizeof(DWORD));
	*pBlock=100;
	
	SetEvent(h);
	while(1)
	{
		if(InterlockedCompareExchange(&i,0,3)==3)
			break;
		Sleep(100);
	}
	ResetEvent(h);
	return 0;
}

DWORD WINAPI Thread2(PVOID p)
{
	HANDLE h=(HANDLE)p;
	DWORD re = WaitForSingleObject(h,INFINITE);
	InterlockedIncrement(&i);
	while(1)
	{
		_tprintf(L"2 thread = %X\n",*pBlock);
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI Thread3(PVOID p)
{
	HANDLE h=(HANDLE)p;
	DWORD re = WaitForSingleObject(h,INFINITE);
	InterlockedIncrement(&i);
	while(1)
	{
		_tprintf(L"3 thread = %X\n",*pBlock);
		Sleep(1000);
	}

	return 0;
}

DWORD WINAPI Thread4(PVOID p)
{
	HANDLE h=(HANDLE)p;
	DWORD re = WaitForSingleObject(h,INFINITE);
	InterlockedIncrement(&i);
	while(1)
	{
		_tprintf(L"4 thread = %X\n",*pBlock);
		Sleep(1000);
	}

	return 0;
}


int main()
{
	DWORD dwBytes;
	HANDLE hEvent=CreateEvent(NULL,TRUE,TRUE,NULL);

	CreateThread(NULL,0,Thread1,hEvent,0,NULL);
	CreateThread(NULL,0,Thread2,hEvent,0,NULL);
	CreateThread(NULL,0,Thread3,hEvent,0,NULL);
	CreateThread(NULL,0,Thread4,hEvent,0,NULL);
	_gettchar();
	return 0;

}

/*

HANDLE WINAPI CreateEvent(
  __in_opt  LPSECURITY_ATTRIBUTES lpEventAttributes,
  __in      BOOL bManualReset,
  __in      BOOL bInitialState,
  __in_opt  LPCTSTR lpName
);

lpEventAttributes:	NULL
bManualReset:		是否手动复位：FALSE代表自动，TRUE是手动
bInitialState：		这个事件对象的初始状态。TRUE标识有信号，FALSE表示没有信号。


多个线程等待一个资源有效，那么此时使用手动复位模式，同事要考虑复位，也就是将事件置于微信号状态的时机。

有效资源是互斥的，在有资源有效的状态下，只能有一个线程使用这个资源，那么此时使用手动模式。

置于事件被创造成功后，开始是有信号还是无信号状态，根据实际情况来判断。


WaitForMultipleObjects



*/