#include"Spin.h"

//��Global_Spin==0��ʱ��˵����û���߳̽���ؼ����룬��Global_Spin==1��ʱ��˵�����߳̽����˹ؼ���
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
