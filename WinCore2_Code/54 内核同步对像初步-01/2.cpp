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

hHandle:		Ҫ�ȴ����ں˶�����
dwMilliseconds:	�ȴ���ʱ�䣬��λ�Ǻ��롣

return:			
		
	WAIT_OBJECT_0:	˵���ȴ��ɹ������ȴ��ں˶����Ϊ���ź�״̬��0x00000000L
	WAIT_TIMEOUT:	�ȴ�ʱ��dwMilliseconds�Ѿ��ľ����������ء�0x00000102L
	WAIT_FAILED:	һ���ǵȴ��ľ�����ԡ�		(DWORD)0xFFFFFFFF


DWORD WINAPI WaitForMultipleObjects(
  __in  DWORD nCount,
  __in  const HANDLE *lpHandles,
  __in  BOOL bWaitAll,
  __in  DWORD dwMilliseconds
);


*/