#include<Windows.h>
#include<tchar.h>

VOID CALLBACK APCProc(
  __in  ULONG_PTR dwParam
)
{
	_tprintf(L"This Apc has been running other\n");
	for(int i=0;i<10;i++)
	{
		_tprintf(L"%d \n",i);
		Sleep(500);
	}
	return;
}

int _tmain()
{
	HANDLE hEvent=CreateEvent(NULL,FALSE,TRUE,NULL);

	QueueUserAPC(APCProc,GetCurrentThread(),NULL);

	DWORD re = WaitForSingleObjectEx(hEvent,INFINITE,TRUE);

	_tprintf(L"re = %X\n",re);

	re = WaitForSingleObject(hEvent,INFINITE);

	_tprintf(L"re = %X\n",re);

	_gettchar();

	return 0;


}