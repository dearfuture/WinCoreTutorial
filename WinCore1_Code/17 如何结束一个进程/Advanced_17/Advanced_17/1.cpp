#include<Windows.h>
#include<tchar.h>

class A
{
public:
	A()
	{
		_tprintf(L"Constructor!\n");
	}
	~A()
	{
		_tprintf(L"Destructor!\n");
	}
};

DWORD WINAPI ThreadProc(
  __in  LPVOID lpParameter
)
{
	//_tprintf(L"Thread sleeping!\n");
	//Sleep(INFINITE);//������߳����޳�˯��ȥ��

	_tprintf(L"the Thread will exit in two seconds\n");
	Sleep(2000);
	//ExitProcess(0);//�˳������̣�
	return 0;
}



int _tmain()
{
	/*
	DWORD dwThreadID=0;
	DWORD dwExitCode;

	
	CreateThread(NULL,0,ThreadProc,NULL,0,&dwThreadID);//����һ���߳�

	_tprintf(L"the Sleeping Thread ID is %d\n",dwThreadID);

	_tprintf(L"exit 4828 process\n");

	_gettchar();
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,3068);

	TerminateProcess(hProcess,444);
	//���������һ���첽���������ԣ�������������ص�ʱ�򣬽��̿��ܻ�û�н���
	//���ԣ���ʱ��ĵķ���ֵ�ǣ�STILL_ACTIVE=259�����ԣ�����Ҫ�Ƚ���������
	//�˳��Ժ�������ȡ�˳��롣

	WaitForSingleObject(hProcess,INFINITE);
	

	BOOL re=GetExitCodeProcess(hProcess,&dwExitCode);

	_tprintf(L"Exit Code is %d\n",dwExitCode);



	CloseHandle(hProcess);
	*/


	{
		A a;
		ExitProcess(0);

	}
	
	_gettchar();
	return 0;
}

