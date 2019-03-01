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
	//Sleep(INFINITE);//让这个线程无限沉睡下去。

	_tprintf(L"the Thread will exit in two seconds\n");
	Sleep(2000);
	//ExitProcess(0);//退出本进程！
	return 0;
}



int _tmain()
{
	/*
	DWORD dwThreadID=0;
	DWORD dwExitCode;

	
	CreateThread(NULL,0,ThreadProc,NULL,0,&dwThreadID);//创建一个线程

	_tprintf(L"the Sleeping Thread ID is %d\n",dwThreadID);

	_tprintf(L"exit 4828 process\n");

	_gettchar();
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,3068);

	TerminateProcess(hProcess,444);
	//这个函数是一个异步函数，所以，当这个函数返回的时候，进程可能还没有结束
	//所以，此时后的的返回值是：STILL_ACTIVE=259。所以，我们要等进程真正被
	//退出以后，再来获取退出码。

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

