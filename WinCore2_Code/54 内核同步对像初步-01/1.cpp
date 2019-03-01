/*
内核同步对象

1. 进程1创建一个文件，给文件中写入数据，那么进程2，在进程1创建完这个文件并写入数据后，进程2在读取这个文件中的内容。

事件内核对象。

1.1 创建打开内核对象hEvent；
1.2 创建文件，写入数据；
1.3 将内核对象hEvent设置到有信号状态。



2.1 创建打开内核对象hEvent；
2.2 等待内核对象有信号；
2.3 打开文件，读取数据。

*/


#include<Windows.h>
#include<tchar.h>

TCHAR str[0x100]=L"abc";


int main()
{
	DWORD dwBytes;
	HANDLE hEvent=CreateEvent(NULL,FALSE,FALSE,L"ydm");

	_tprintf(L"GetLastError = %d\n",GetLastError());

	HANDLE hFile=CreateFile(L"E:\\test\\1.x",GENERIC_ALL,0,NULL,CREATE_ALWAYS,0,NULL);

	WriteFile(hFile,str,0x100*2,&dwBytes,NULL);

	CloseHandle(hFile);

	SetEvent(hEvent);


	_gettchar();
	return 0;

}