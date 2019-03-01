#include<Windows.h>
#include<tchar.h>

int _tmain()
{

	STARTUPINFO info;
	ZeroMemory(&info,sizeof(info));
	info.cb=sizeof(info);
	PROCESS_INFORMATION si;



	CreateProcess(L"C:\\Windows\\system32\\calc.exe",NULL,
		NULL,NULL,FALSE,NULL,NULL,NULL,&info,&si);


	_gettchar();
	return 0;
}