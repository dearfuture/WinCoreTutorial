/*
�ں�ͬ������

1. ����1����һ���ļ������ļ���д�����ݣ���ô����2���ڽ���1����������ļ���д�����ݺ󣬽���2�ڶ�ȡ����ļ��е����ݡ�

�¼��ں˶���

1.1 �������ں˶���hEvent��
1.2 �����ļ���д�����ݣ�
1.3 ���ں˶���hEvent���õ����ź�״̬��



2.1 �������ں˶���hEvent��
2.2 �ȴ��ں˶������źţ�
2.3 ���ļ�����ȡ���ݡ�

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
bManualReset:		�Ƿ��ֶ���λ��FALSE�����Զ���TRUE���ֶ�
bInitialState��		����¼�����ĳ�ʼ״̬��TRUE��ʶ���źţ�FALSE��ʾû���źš�


����̵߳ȴ�һ����Դ��Ч����ô��ʱʹ���ֶ���λģʽ��ͬ��Ҫ���Ǹ�λ��Ҳ���ǽ��¼�����΢�ź�״̬��ʱ����

��Ч��Դ�ǻ���ģ�������Դ��Ч��״̬�£�ֻ����һ���߳�ʹ�������Դ����ô��ʱʹ���ֶ�ģʽ��

�����¼�������ɹ��󣬿�ʼ�����źŻ������ź�״̬������ʵ��������жϡ�


WaitForMultipleObjects



*/