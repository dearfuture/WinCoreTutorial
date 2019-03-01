/* WaitForMultipleObjects


DWORD WINAPI WaitForMultipleObjects(
  __in  DWORD nCount,
  __in  const HANDLE *lpHandles,
  __in  BOOL bWaitAll,
  __in  DWORD dwMilliseconds
);

const HANDLE *lpHandles:	�ȴ����ں˶���ľ������	
DWORD nCount:				�ȴ��ں˶�����������Ԫ�صĸ���
BOOL bWaitAll:				�Ǳ�ʾ���ȴ��������ں˶���Ϊ���ź�״̬ʱ���ú������أ����ʾֻҪ��һ�����ȴ����ں˶����Ϊ���ź�״̬����������
DWORD dwMilliseconds:		�ȴ�ʱ������

Return��
		
		WAIT_OBJECT_0 to (WAIT_OBJECT_0 + nCount�C 1)��		���bWaitAll==TRUE����ô����ֵ��ʾ���б��ȴ��ں˶����Ѿ������ź�״̬�����bWaitAll==FALSE����ʾ���ź��ں˶����������е�����
		WAIT_ABANDONED_0 to (WAIT_ABANDONED_0 + nCount�C 1)��	���bWaitAll==TRUE,��ʱ����Ϊ���������ֵ�Ļ������б��ȴ����ں˶��������ź�״̬�����bWaitAll==FALSE�������ٽ�������ͻ�������йء�
		WAIT_TIMEOUT	0x00000102L							�ȴ�ʱ�䳬ʱ
		WAIT_FAILED											һ���Ǿ������


bWaitAll:	�����ֵΪTRUE��ʱ�����б��ȴ����ں˶������ͬʱ�������ź�״̬������������ܷ��ء�

�����������ܵȴ�64���ں˶���
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
һ����˵����ȫ�ȴ������ȼ�Ҫ��һЩ��



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