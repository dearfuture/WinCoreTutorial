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
	//��������������������У�ֻ�е�si.hProcess�����Ƴ���
	//��������ŷ��ء�

	_tprintf(L"child_process Exited!\n");

	CloseHandle(si.hProcess);//֪��������������ã���������ӽ��̵��ں˶��󣬲ſ��ܱ����١�



	_gettchar();
	return 0;

}