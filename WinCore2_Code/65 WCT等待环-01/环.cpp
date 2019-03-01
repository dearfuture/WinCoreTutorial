#include<Windows.h>
#include<tchar.h>
#include<Wct.h>



VOID CALLBACK WaitChainCallback(
    HWCT WctHandle,
    DWORD_PTR Context,
    DWORD CallbackStatus,
    LPDWORD NodeCount,
    PWAITCHAIN_NODE_INFO NodeInfoArray,
    LPBOOL IsCycle
)
{

	_gettchar();
}


BOOL
GrantDebugPrivilege ( )
/*++

Routine Description:

    Enables the debug privilege (SE_DEBUG_NAME) for this process.
    This is necessary if we want to retrieve wait chains for processes
    not owned by the current user.

Arguments:

    None.

Return Value:

    TRUE if this privilege could be enabled; FALSE otherwise.

--*/
{
    BOOL             fSuccess    = FALSE;
    HANDLE           TokenHandle = NULL;
    TOKEN_PRIVILEGES TokenPrivileges;

    if (!OpenProcessToken(GetCurrentProcess(),
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                          &TokenHandle))
    {
        _tprintf(L"Could not get the process token");
        goto Cleanup;
    }

    TokenPrivileges.PrivilegeCount = 1;

    if (!LookupPrivilegeValue(NULL,
                              SE_DEBUG_NAME,
                              &TokenPrivileges.Privileges[0].Luid))
    {
        _tprintf(L"Couldn't lookup SeDebugPrivilege name");
        goto Cleanup;
    }

    TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!AdjustTokenPrivileges(TokenHandle,
                               FALSE,
                               &TokenPrivileges,
                               sizeof(TokenPrivileges),
                               NULL,
                               NULL))
    {
        _tprintf(L"Could not revoke the debug privilege");
        goto Cleanup;
    }

    fSuccess = TRUE;

 Cleanup:

    if (TokenHandle)
    {
        CloseHandle(TokenHandle);
    }

    return fSuccess;
}

DWORD WINAPI Thread1(PVOID)
{
	while(1)
	{
		Sleep(1000);
	}
	return 0;
}




int _tmain()
{


	WAITCHAIN_NODE_INFO NodeInfoArray[WCT_MAX_NODE_COUNT];
    DWORD               Count, i;
    BOOL                IsCycle;

	BOOL re = GrantDebugPrivilege ( );


	//HANDLE hThread1=CreateThread(NULL,0,Thread1,NULL,0,NULL);
	//DWORD  Id1=GetThreadId(hThread1);

	HWCT hWct=OpenThreadWaitChainSession(WCT_ASYNC_OPEN_FLAG,WaitChainCallback);
	//HWCT hWct=OpenThreadWaitChainSession(0,NULL);
	//_gettchar();

	Count=WCT_MAX_NODE_COUNT;

	DWORD_PTR  context =1;

	re=GetThreadWaitChain(hWct,context,WCTP_GETINFO_ALL_FLAGS,17304,&Count,NodeInfoArray,&IsCycle);
	///re=GetThreadWaitChain(hWct,NULL,WCTP_GETINFO_ALL_FLAGS,222,&Count,NodeInfoArray,&IsCycle);
	//re=GetThreadWaitChain(hWct,NULL,WCTP_GETINFO_ALL_FLAGS,44,&Count,NodeInfoArray,&IsCycle);

	_gettchar();
	CloseThreadWaitChainSession(hWct);
	return 0;
}

