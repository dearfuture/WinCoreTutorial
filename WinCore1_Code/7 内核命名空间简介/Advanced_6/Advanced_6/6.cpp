#include<Windows.h>
#include<tchar.h>

int _tmain()
{
	HANDLE hMutex=CreateMutex(NULL,FALSE,L"ydm\\ydm");//创建了一个名字叫NULL的互斥内核对象
	//匿名内核对象：就是没有名字的内核对象，这种内核对象，不能在进程间共享。
	//命名内核对象可以在进程间共享。
	//GUID=:全局唯一标识符Global Unique identification

	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{
		//_tprintf(L"%s,\n",L"this is the next instance!");
		return 0;
	}

	DWORD sessionid=0;
	DWORD processid=0;
	processid=GetProcessId(GetCurrentProcess());//获取当前进程进程ID
	//GetCurrentProcess()获得当前进程句柄！
	
	if(ProcessIdToSessionId(processid,&sessionid))//获取当前程序运行在那个session或者说会话中！
		_tprintf(L"%s,%d\n",L"this is the first instance! and session id is ",sessionid);
	
	_gettchar();
	return 0;
}