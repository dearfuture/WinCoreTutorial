#include"Spin.h"

typedef struct
{
	DWORD Critical_Num;//�����ؼ������̸߳���
	DWORD Id[0x1000];//��������ܱ�������Щ���̵߳�ID
	DWORD Run[0x1000];//Run�е�Run[1]==1˵����Id[1]����߳������ڹؼ���
	DWORD Sus[0x1000];//Sus[1]==1˵������̱߳�����
	HANDLE h;
}CRITICAL,*PCRITICAL;

PCRITICAL CreateCritical();

DWORD EnterCritical(PCRITICAL pCritical);

DWORD LeaveCritical(PCRITICAL pCritical);

DWORD DeleteCritical(PCRITICAL pCritical); 

