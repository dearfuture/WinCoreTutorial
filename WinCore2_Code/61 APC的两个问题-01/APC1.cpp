#include<Windows.h>
#include<tchar.h>
#include<stdio.h>

/*
 �Ƿ���Խ�һ�����̵ĺ�����ע�뵽����һ�����̵��߳��С�

*/

VOID CALLBACK APCProc(
  __in  ULONG_PTR dwParam
)
{
	_tprintf(L"This Apc has been running other\n");
	return;
}


typedef VOID  (CALLBACK *LLL)(ULONG_PTR);

int _tmain()
{
	HANDLE hThread = OpenThread(GENERIC_ALL,FALSE,10892);
	DWORD re = QueueUserAPC((LLL)20910385,hThread,NULL);

	_tprintf(L" re  = %d \n",re);

	_gettchar();
	
	return 0;


}