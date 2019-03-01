#include<Windows.h>
#include<tchar.h>

int _tmain()
{
	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

   

    // Start the child process. 
    if( !CreateProcess(L"Test_Dlg.exe",   // No module name (use command line)
        NULL,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        _tprintf(L"CreateProcess failed (%d).\n", GetLastError() );
        return 0;
    }
	
	DWORD re = WaitForInputIdle(pi.hProcess,INFINITE);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	_tprintf(L" re = %X\n",re);
	_gettchar();
	return 0;
}