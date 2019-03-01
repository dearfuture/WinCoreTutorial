#include<Windows.h>
#include<tchar.h>

int _tmain()
{
	STARTUPINFO info;
	ZeroMemory(&info,sizeof(info));
	info.cb=sizeof(info);


	PROCESS_INFORMATION si;

	info.dwFlags=STARTF_USESHOWWINDOW;
	info.wShowWindow=1;


	_tprintf(L"CreateProces\n",GetLastError());

	TCHAR CommandLine[200]=L"\"D:/yd m/Test.exe\" abc 123";

	if(!CreateProcess(NULL,CommandLine,
		NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&info,&si))
	{
		_tprintf(L"CreateProcess failure!=%d\n",GetLastError());

		_gettchar();
		return 0;
	}

	_tprintf(L"Waiting for child_process Exit\n");

	WaitForSingleObject(si.hProcess,INFINITE);
	//这个函数会阻塞程序运行，只有当si.hProcess进程推出后，
	//这个函数才返回。

	_tprintf(L"child_process Exited!\n");

	CloseHandle(si.hProcess);//知道这个函数被调用，代表这个子进程的内核对象，才可能被销毁。



	_gettchar();
	return 0;

}