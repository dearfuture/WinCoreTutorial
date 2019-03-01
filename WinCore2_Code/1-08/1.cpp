/* WaitForMultipleObjects


DWORD WINAPI WaitForMultipleObjects(
  __in  DWORD nCount,
  __in  const HANDLE *lpHandles,
  __in  BOOL bWaitAll,
  __in  DWORD dwMilliseconds
);

const HANDLE *lpHandles:	等待的内核对象的句柄数组	
DWORD nCount:				等待内核对象句柄数组中元素的个数
BOOL bWaitAll:				是表示被等待的所有内核对象都为有信号状态时，该函数返回，否表示只要有一个被等待的内核对象变为有信号状态，函数返回
DWORD dwMilliseconds:		等待时间限制

Return：
		
		WAIT_OBJECT_0 to (WAIT_OBJECT_0 + nCount– 1)：		如果bWaitAll==TRUE，那么返回值表示所有被等待内核对象都已经是有信号状态，如果bWaitAll==FALSE，表示有信号内核对象在数组中的索引
		WAIT_ABANDONED_0 to (WAIT_ABANDONED_0 + nCount– 1)：	如果bWaitAll==TRUE,暂时先认为，返回这个值的话，所有被等待的内核对象都是有信号状态，如果bWaitAll==FALSE，后续再讲，这个和互斥对象有关。
		WAIT_TIMEOUT	0x00000102L							等待时间超时
		WAIT_FAILED											一般是句柄错误


bWaitAll:	当这个值为TRUE的时候，所有被等待的内核对象必须同时处于有信号状态，这个函数才能返回。

这个函数最多能等待64个内核对象。
*/
#include<Windows.h>
#include<tchar.h>



HANDLE h[40]={0};


DWORD WINAPI Thread(PVOID)
{
	DWORD re = WaitForMultipleObjects(2,h,TRUE,INFINITE);
	_tprintf(L"Index = %d\n",re-WAIT_OBJECT_0);
	_gettchar();
	return 0;


}


DWORD WINAPI Thread2(PVOID)
{
	//Sleep(5000);
	DWORD re = WaitForMultipleObjects(2,h,FALSE,INFINITE);
	_tprintf(L"2222222222222Index = %d\n",re-WAIT_OBJECT_0);
	_gettchar();
	return 0;


}

/*
一般来说，不全等待的优先级要高一些。



*/


int _tmain()
{
	for(int i=0;i<40;i++)
	{
		h[i]=CreateEvent(NULL,FALSE,FALSE,NULL);
	}


	CreateThread(NULL,0,Thread,NULL,0,NULL);
	CreateThread(NULL,0,Thread2,NULL,0,NULL);


	_gettchar();
	
	SetEvent(h[1]);
	_gettchar();

	SetEvent(h[0]);

	_gettchar();

	return 0;


}