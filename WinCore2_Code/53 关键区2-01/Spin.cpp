#include"Spin.h"

//当Global_Spin==0的时候，说明，没有线程进入关键代码，当Global_Spin==1的时候，说明有线程进入了关键区
long Global_Spin=0;


DWORD EnterGlobalSpin()
{
	while(InterlockedCompareExchange(&Global_Spin,1,0))
	{
		Sleep(20);
	}
	return 0;
}


DWORD LeaveGlobalSpin()
{
	InterlockedCompareExchange(&Global_Spin,0,1);
	return 0;
}
