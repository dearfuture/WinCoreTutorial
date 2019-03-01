#include<Windows.h>

#include<tchar.h>

#include<Winternl.h>

typedef NTSTATUS (WINAPI *QT)(HANDLE,PROCESSINFOCLASS,PVOID,ULONG,PULONG);


TCHAR* GetProcessCommandLine(HANDLE hProcess)
{
	HMODULE hModule=0;
	QT NtQuery;
	hModule=LoadLibrary(L"Ntdll.dll");
	if(hModule)
	{
		NtQuery=(QT)GetProcAddress(hModule,"NtQueryInformationProcess");
		if(NtQuery==NULL)
			return 0;
	}
	else
		return 0;
	
	

	PROCESS_BASIC_INFORMATION pi={0};

	NTSTATUS re=NtQuery(hProcess,
		ProcessBasicInformation,&pi,sizeof(pi),NULL);

	/*
	在pi中，pi.PebBaseAddress指向PEB，那么这个指针指向的地址，是那个地址呢？
	这个指针指向的地址，是word进程中的地址！！！
	*/

	if(!NT_SUCCESS(re))
	{
		//_tprintf(L"OK");
		return 0;
	}

	PEB peb;
	RTL_USER_PROCESS_PARAMETERS para;

	ReadProcessMemory(hProcess,pi.PebBaseAddress,&peb,sizeof(peb),NULL);

	ReadProcessMemory(hProcess,peb.ProcessParameters,&para,sizeof(para),NULL);

	TCHAR* CommandLine=(TCHAR*)malloc(sizeof(TCHAR)*1024);

	ReadProcessMemory(hProcess,para.CommandLine.Buffer,CommandLine,1024*2,NULL);

	//_tprintf(L"%s\n",CommandLine);

	//MessageBox(NULL,CommandLine,L"OK",MB_OK);

	CloseHandle(hProcess);
	FreeLibrary(hModule);
	return CommandLine;

}





int _tmain(int argc,TCHAR* argv[])
{

	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,5084);
	TCHAR* str=GetProcessCommandLine(hProcess);

	MessageBox(NULL,str,L"OK",MB_OK);

	free(str);
	return 0;


}