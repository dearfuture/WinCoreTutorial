#include<Windows.h>
#include<tchar.h>

int _tmain()
{
	TCHAR buf[1024];
	DWORD i;
	i=GetEnvironmentVariable(L"ydm",buf,1024);
	i=GetLastError();
	_tprintf(L"%s\n",buf);
	SetEnvironmentVariable(L"ydm",L"ribenren");//只能改变当前进程的环境变量。

	i=GetEnvironmentVariable(L"ydm",buf,1024);

	_tprintf(L"%s\n",buf);


	_gettchar();
	return 0;
}