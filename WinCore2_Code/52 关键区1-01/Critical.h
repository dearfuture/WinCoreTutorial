#include"Spin.h"

typedef struct
{
	DWORD Critical_Num;//�����ؼ������̸߳���
	DWORD Id[0x1000];//��������ܱ�������Щ���̵߳�ID
}CRITICAL,*PCRITICAL;

PCRITICAL CreateCritical();

DWORD EnterCritical(PCRITICAL pCritical);

DWORD LeaveCritical(PCRITICAL pCritical);

DWORD DeleteCritical(PCRITICAL pCritical); 

