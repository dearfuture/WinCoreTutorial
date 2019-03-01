#include<Windows.h>
#include<tchar.h>
#include<Tlhelp32.h>

int _tmain()
{
	HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 pe={0};
	pe.dwSize=sizeof(pe);
	Process32First(hSnapshot,&pe);

	DWORD processID=0;
	do
	{
		_tprintf(L"%d:%s\n",pe.th32ProcessID,pe.szExeFile);
		if(CSTR_EQUAL==CompareStringOrdinal(L"ThunderMini.exe",11,pe.szExeFile,11,TRUE))
		{
			processID=pe.th32ProcessID;
		}	
	}while(Process32Next(hSnapshot,&pe));

	if(!processID)
	{
		_tprintf(L"not fund ThunderMini.exe process\n");
		_gettchar();
		return 0;
	}

	CloseHandle(hSnapshot);

	hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPALL,processID);
	//注意，这个快照，并不是拍摄的某个进程中线程的id，他拍到的是系统中所有线程。

	THREADENTRY32 te={0};
	te.dwSize=sizeof(te);
	BOOL re=Thread32First(hSnapshot,&te);
	do
	{
		if(te.th32OwnerProcessID==processID)
		{
			DWORD code=0;
			GetExitCodeThread(OpenThread(THREAD_ALL_ACCESS,FALSE,te.th32ThreadID),&code);
			_tprintf(L"%d:%d:%d\n",te.th32OwnerProcessID,te.th32ThreadID,code);
		}

	}while(Thread32Next(hSnapshot,&te));

	DWORD code=0;
	HANDLE hThread=OpenThread(THREAD_ALL_ACCESS,FALSE,15264);
	GetExitCodeThread(hThread,&code);


	_gettchar();
	CloseHandle(hSnapshot);
	return 0;
}