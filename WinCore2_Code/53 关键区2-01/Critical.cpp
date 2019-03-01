#include"Critical.h"


DWORD WINAPI CriticalThread(PVOID p)
{
	PCRITICAL pCritical=(PCRITICAL)p;

	while(1)
	{
		EnterGlobalSpin();

		for(int i=0;i<pCritical->Critical_Num;i++)
		{
			//第0个线程的处理方式
			if(i==0)
			{
				if(pCritical->Run[0])//如果第0个线程在运行，继续检查下一个
				{
					continue;
				}
				else//如果第一个线程没有运行
				{
					if(pCritical->Sus[0])//如果第0个线程被挂起
					{
						HANDLE h=OpenThread(GENERIC_ALL,0,pCritical->Id[0]);
						ResumeThread(h);
						CloseHandle(h);
						pCritical->Run[0]=1;
					}
					else//如果第0个线程没有被挂起
					{
						pCritical->Run[0]=1;
					}
					continue;
				}

			}
			//其他线程的处理方式
			else if(pCritical->Sus[i]==0)//如果线程没有被挂起，那么挂起
			{
				HANDLE h=OpenThread(GENERIC_ALL,0,pCritical->Id[i]);
				SuspendThread(h);
				CloseHandle(h);
				pCritical->Sus[i]=1;
				continue;
			}
			else if(pCritical->Sus[i])
				continue;
		}


		LeaveGlobalSpin();

		Sleep(1);
	}


}


PCRITICAL CreateCritical()
{
	PCRITICAL p=(PCRITICAL)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(CRITICAL));
	p->h=CreateThread(NULL,0,CriticalThread,p,0,NULL);
	return p;
}

DWORD EnterCritical(PCRITICAL pCritical)
{
	
	DWORD Id=GetCurrentThreadId();
	EnterGlobalSpin();
	if(pCritical->Critical_Num==0)//没有其他线程进入关键代码
	{
		pCritical->Id[pCritical->Critical_Num]=Id;
		pCritical->Run[pCritical->Critical_Num]=1;
		pCritical->Sus[pCritical->Critical_Num]=0;
		pCritical->Critical_Num=1;
		LeaveGlobalSpin();
		return 0;
	}
	else//有其他线程进入关键代码
	{
		pCritical->Id[pCritical->Critical_Num]=Id;
		//Index=pCritical->Critical_Num;
		pCritical->Critical_Num++;
		LeaveGlobalSpin();
		while(1)//检查线程是否可以进入关键区代码
		{
			if(pCritical->Id[0]==Id)
			{
				if(pCritical->Run[0])
					break;
			}
		}
		return 0;
	}
}

DWORD LeaveCritical(PCRITICAL pCritical)
{
	EnterGlobalSpin();
	if(pCritical->Critical_Num==1)//只有一个线程在关键代码需要离开的时候
	{
		pCritical->Critical_Num=0;
		pCritical->Id[0]=0;
		pCritical->Run[0]=0;
		pCritical->Sus[0]=0;
		LeaveGlobalSpin();
		return 0;
	}
	else//还有其他线程等待进入关键区代码
	{
		CopyMemory(&pCritical->Id[0],&pCritical->Id[1],sizeof(DWORD)*(pCritical->Critical_Num-1));
		CopyMemory(&pCritical->Run[0],&pCritical->Run[1],sizeof(DWORD)*(pCritical->Critical_Num-1));
		CopyMemory(&pCritical->Sus[0],&pCritical->Sus[1],sizeof(DWORD)*(pCritical->Critical_Num-1));
		pCritical->Critical_Num--;
		pCritical->Id[pCritical->Critical_Num]=0;
		pCritical->Run[pCritical->Critical_Num]=0;
		pCritical->Sus[pCritical->Critical_Num]=0;
		LeaveGlobalSpin();
		return 0;
	}
}

DWORD DeleteCritical(PCRITICAL pCritical)
{

	TerminateThread(pCritical->h,0);
	HeapFree(GetProcessHeap(),0,pCritical);
	return 0;

}