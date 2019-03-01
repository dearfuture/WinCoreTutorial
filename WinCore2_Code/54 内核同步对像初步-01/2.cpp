#include<Windows.h>
#include<tchar.h>

TCHAR str[0x100]={0};

int _tmain()
{
	DWORD dwBytes;
	HANDLE hEvent=CreateEvent(NULL,FALSE,FALSE,L"ydm");
	HANDLE hhh=NULL;
	_tprintf(L"GetLastError = %d\n",GetLastError());

	DWORD re = WaitForSingleObject(hEvent,-1);

	if(re==WAIT_OBJECT_0)
	{

	
		HANDLE hFile=CreateFile(L"E:\\test\\1.x",GENERIC_ALL,0,NULL,OPEN_ALWAYS,0,NULL);

		ReadFile(hFile,str,0x100*2,&dwBytes,NULL);

		CloseHandle(hFile);
	}
	if(re==WAIT_TIMEOUT)
	{
		_tprintf(L"shijian haojin\n");
	}

	_gettchar();

	CloseHandle(hEvent);

	return 0;
}

/*
DWORD WINAPI WaitForSingleObject(
  __in  HANDLE hHandle,
  __in  DWORD dwMilliseconds
);

hHandle:		要等待的内核对象句柄
dwMilliseconds:	等待的时间，单位是毫秒。

return:			
		
	WAIT_OBJECT_0:	说明等待成功，被等待内核对象变为有信号状态。0x00000000L
	WAIT_TIMEOUT:	等待时间dwMilliseconds已经耗尽，函数返回。0x00000102L
	WAIT_FAILED:	一般是等待的句柄不对。		(DWORD)0xFFFFFFFF


DWORD WINAPI WaitForMultipleObjects(
  __in  DWORD nCount,
  __in  const HANDLE *lpHandles,
  __in  BOOL bWaitAll,
  __in  DWORD dwMilliseconds
);


*/