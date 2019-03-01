#include<Windows.h>
#include<tchar.h>

int _tmain()
{
	HANDLE hProcess=GetCurrentProcess();
	//GetCurrentProcess函数，无论在什么情况下，他都返回-1！！！！
	//我们把GetCurrentProcess函数返回的句柄，叫伪句柄，当前请情况下，这个伪句柄一定是-1，但是
	//不保证以后韩式-1.

	_tprintf(L"hProcess=%d\n",hProcess);

	DWORD sessionid=0;
	DWORD processid=0;
	processid=GetProcessId((HANDLE)-1);//获取当前进程进程ID
	//GetCurrentProcess()获得当前进程句柄！
	

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