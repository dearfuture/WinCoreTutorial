#include<Windows.h>
#include<tchar.h>

int _tWinMain(HINSTANCE,HINSTANCE,TCHAR* CommandLine,int)
{
	TCHAR* pTemp;
	_tprintf(L"%s\n",CommandLine);//CommandLine参数，不含有程序命令。

	pTemp=GetCommandLine();

	/*
	这个函数此时获得的命令行字符串，包括可执行程序的名字和参数，他们被放到一个字符串中，

	注意：可执行程序的名字，被引号引起来了。


	*/

	return 0;
}