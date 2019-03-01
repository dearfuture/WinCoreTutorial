#include"Critical.h"

PCRITICAL CreateCritical()
{
	PCRITICAL p=(PCRITICAL)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(CRITICAL));
	return p;
}

DWORD EnterCritical(PCRITICAL pCritical)
{
	DWORD Id=GetCurrentThreadId();
	EnterGlobalSpin();
	if(pCritical->Critical_Num==0)
	{
		pCritical->Id[pCritical->Critical_Num]=Id;
		pCritical->Critical_Num=1;
		LeaveGlobalSpin();
		return 0;
	}
	else
	{
		pCritical->Id[pCritical->Critical_Num]=Id;
		pCritical->Critical_Num++;
		LeaveGlobalSpin();
		//Sleep(200);
		SuspendThread(GetCurrentThread());
		return 0;
	}
}

DWORD LeaveCritical(PCRITICAL pCritical)
{
	EnterGlobalSpin();
	if(pCritical->Critical_Num==1)
	{
		pCritical->Critical_Num=0;
		pCritical->Id[0]=0;
		LeaveGlobalSpin();
		return 0;
	}
	else
	{
		CopyMemory(&pCritical->Id[0],&pCritical->Id[1],sizeof(DWORD)*(pCritical->Critical_Num-1));
		pCritical->Critical_Num--;
		pCritical->Id[pCritical->Critical_Num]=0;

		HANDLE h=OpenThread(GENERIC_ALL,0,pCritical->Id[0]);
		ResumeThread(h);
		CloseHandle(h);

		LeaveGlobalSpin();
		return 0;


	}
}

DWORD DeleteCritical(PCRITICAL pCritical)
{
	HeapFree(GetProcessHeap(),0,pCritical);
	return 0;

}