#include"Critical.h"

PCRITICAL pCritical;
DWORD s=0;

DWORD WINAPI Thread(PVOID)
{
	EnterCritical(pCritical);
	for(int i=0;i<100;i++)
	{
		_tprintf(L"i = %d threadID = %X s = %d\n",i,GetCurrentThreadId(),s);
	}
	s++;
	LeaveCritical(pCritical);
	return 0;
}

int _tmain()
{
	pCritical=CreateCritical();
	for(int i=0;i<1000;i++)
	{
		CreateThread(NULL,0,Thread,NULL,0,NULL);
	}

	_gettchar();
	DeleteCritical(pCritical);
	return 0;
}