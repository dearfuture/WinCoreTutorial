#include"Spin.h"

typedef struct
{
	DWORD Critical_Num;//想进入关键区的线程个数
	DWORD Id[0x1000];//这个数组总保存着这些个线程的ID
	DWORD Run[0x1000];//Run中的Run[1]==1说明，Id[1]这个线程运行在关键区
	DWORD Sus[0x1000];//Sus[1]==1说明这个线程被挂起
	HANDLE h;
}CRITICAL,*PCRITICAL;

PCRITICAL CreateCritical();

DWORD EnterCritical(PCRITICAL pCritical);

DWORD LeaveCritical(PCRITICAL pCritical);

DWORD DeleteCritical(PCRITICAL pCritical); 

