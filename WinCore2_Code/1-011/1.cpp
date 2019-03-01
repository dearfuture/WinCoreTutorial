#include<Windows.h>
#include<tchar.h>
/*
CreateSemaphore
OpenSemaphore
ReleaseSemaphore
WaitForSingleObject
WaitForMultipleObjects

�źŵƿ�����Ϊ��һ���ܹ���סͨ�г��������ĺ��̵ƣ����̵ƣ����źţ�ʱ���������ȴ��źŵƵ��̣߳�����ͬ�У����ź�ʱ���������ȴ��źŵƵ��̣߳�������ͬ�С�

ʹ��CreateSemaphore���������źŵơ�
ʹ��ReleaseSemaphore�����������źŵ����������е��̸߳�����
WaiForSingleObject��WaiForMultipleObjects����ÿ�ȴ��ɹ�һ�Σ�����һ���źŵƵ�ͬ�и�����






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