#include<Windows.h>
#include<tchar.h>

int _tmain()
{
	HANDLE hProcess=GetCurrentProcess();
	//GetCurrentProcess������������ʲô����£���������-1��������
	//���ǰ�GetCurrentProcess�������صľ������α�������ǰ������£����α���һ����-1������
	//����֤�Ժ�ʽ-1.

	_tprintf(L"hProcess=%d\n",hProcess);

	DWORD sessionid=0;
	DWORD processid=0;
	processid=GetProcessId((HANDLE)-1);//��ȡ��ǰ���̽���ID
	//GetCurrentProcess()��õ�ǰ���̾����
	

	HANDLE hProcess1=OpenProcess(PROCESS_ALL_ACCESS,FALSE,GetProcessId((HANDLE)-1));
	
	HANDLE hProcess2,hProcess3;

	DuplicateHandle((HANDLE)-1,(HANDLE)-1,(HANDLE)-1,&hProcess2,NULL,FALSE,0);
	DuplicateHandle((HANDLE)-1,(HANDLE)-1,(HANDLE)-1,&hProcess3,NULL,FALSE,0);

	_tprintf(L"hprocess1=%0x\nhprocess2=%0x\nhProcess3=%0x\n",hProcess1,hProcess2,hProcess3);

	CloseHandle(hProcess1);
	CloseHandle(hProcess2);
	CloseHandle(hProcess3);

	_gettchar();
	return 0;
}