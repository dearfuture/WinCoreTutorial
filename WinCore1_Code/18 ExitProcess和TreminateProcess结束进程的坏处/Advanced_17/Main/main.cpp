#include<Windows.h>
#include<tchar.h>

int _tmain()
{
	_tprintf(L"\n");
	TCHAR ws_Directory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,ws_Directory);
	_tprintf(L"%s/\n",ws_Directory);
	TCHAR str_Command[MAX_PATH]={0};

	STARTUPINFO start_info={0};
	PROCESS_INFORMATION info={0};

	start_info.cb=sizeof(start_info);
	


	while(CSTR_EQUAL!=CompareStringOrdinal(str_Command,4,L"quit",4,TRUE))
	{
		_tprintf(L"%s/",ws_Directory);
		_getts(str_Command);
		CreateProcess(NULL,str_Command,NULL,NULL,FALSE,0,NULL,NULL,&start_info,&info);
		CloseHandle(info.hProcess);
		CloseHandle(info.hThread);
	}

	_tprintf(L"press any key to quit\n");

	_gettchar();
	return 0;
}