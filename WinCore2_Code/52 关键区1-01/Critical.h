#include"Spin.h"

typedef struct
{
	DWORD Critical_Num;//想进入关键区的线程个数
	DWORD Id[0x1000];//这个数组总保存着这些个线程的ID
}CRITICAL,*PCRITICAL;

PCRITICAL CreateCritical();

DWORD EnterCritical(PCRITICAL pCritical);

DWORD LeaveCritical(PCRITICAL pCritical);

DWORD DeleteCritical(PCRITICAL pCritical); 

