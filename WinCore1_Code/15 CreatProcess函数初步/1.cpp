#include<Windows.h>
#include<tchar.h>

int _tmain()
{

	STARTUPINFO info;
	ZeroMemory(&info,sizeof(info));
	info.cb=sizeof(info);


	PROCESS_INFORMATION si;
	_tprintf(L"CreateProces\n",GetLastError());

	if(!CreateProcess(L"D:/Projects/Advanced_14/Debug/GetCurrentDirectory.exe",NULL,
		NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&info,&si))
	{
		_tprintf(L"CreateProcess failure!=%d\n",GetLastError());

		_gettchar();
		return 0;
	}

	CloseHandle(si.hProcess);
	CloseHandle(si.hThread);
	



	_gettchar();
	return 0;
}