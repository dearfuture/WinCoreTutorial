#include<Windows.h>
#include<tchar.h>
#include<stdio.h>

/*
 是否可以将一个进程的函数，注入到另外一个进程的线程中。

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