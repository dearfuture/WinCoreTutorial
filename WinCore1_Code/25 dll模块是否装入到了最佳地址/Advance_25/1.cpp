#include<Windows.h>

#include<tchar.h>

#include<Tlhelp32.h>

#define ID 736

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

LPFN_ISWOW64PROCESS fnIsWow64Process;

BOOL IsWow64(HANDLE hProcess)
{
    BOOL bIsWow64 = FALSE;

    //IsWow64Process is not available on all supported versions of Windows.
    //Use GetModuleHandle to get a handle to the DLL that contains the function
    //and GetProcAddress to get a pointer to the function if available.

    fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
        GetModuleHandle(TEXT("kernel32")),"IsWow64Process");

    if(NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(hProcess,&bIsWow64))
        {
            //handle error
        }
    }
    return bIsWow64;
}


PVOID GetModulePreferredBaseAddr(DWORD dwProcessId, PVOID pvModuleRemote) {

   PVOID pvModulePreferredBaseAddr = NULL;
   IMAGE_DOS_HEADER idh;
   IMAGE_NT_HEADERS inth;

   // Read the remote module's DOS header
   Toolhelp32ReadProcessMemory(dwProcessId, 
      pvModuleRemote, &idh, sizeof(idh), NULL);

   // Verify the DOS image header
   if (idh.e_magic == IMAGE_DOS_SIGNATURE) {
      // Read the remote module's NT header
      Toolhelp32ReadProcessMemory(dwProcessId, 
         (PBYTE) pvModuleRemote + idh.e_lfanew, &inth, sizeof(inth), NULL);

      // Verify the NT image header
      if (inth.Signature == IMAGE_NT_SIGNATURE) {
         // This is valid NT header, get the image's preferred base address
         pvModulePreferredBaseAddr = (PVOID) inth.OptionalHeader.ImageBase;
      }
   }
   return(pvModulePreferredBaseAddr);
}





int _tmain()
{
	DWORD nFlags;
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,ID);

	nFlags=TH32CS_SNAPMODULE|TH32CS_SNAPMODULE32;
	

	HANDLE hSnapshot=CreateToolhelp32Snapshot(nFlags,ID);


	MODULEENTRY32 me={0};
	me.dwSize=sizeof(me);
	Module32First(hSnapshot,&me);
	do
	{
		

		PVOID pPre=GetModulePreferredBaseAddr(
			ID,me.modBaseAddr);
		if(pPre!=me.modBaseAddr)
			_tprintf(L"hModule=%0X,BaseAddr=%0X,ModSize=%0X,pPre=%0X\n%s\n",
				me.hModule,me.modBaseAddr,me.modBaseSize,pPre,me.szModule);

	}while(Module32Next(hSnapshot,&me));
	

	_gettchar();
	CloseHandle(hProcess);
	return 0;
}