#include<Windows.h>
#include<tchar.h>

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
LPFN_ISWOW64PROCESS fnIsWow64Process;//定义了一个函数指针变量。

BOOL IsWow64()
{
    BOOL bIsWow64 = FALSE;

    //IsWow64Process is not available on all supported versions of Windows.
    //Use GetModuleHandle to get a handle to the DLL that contains the function
    //and GetProcAddress to get a pointer to the function if available.

    fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
        GetModuleHandle(TEXT("kernel32")),"IsWow64Process");

    if(NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
        {
            //handle error
        }
    }
    return bIsWow64;
}

int _tmain()
{
	if(IsWow64())
	{
		_tprintf(L"This process under Wow64!\n");
		//说明当前操作系统是64位
		//启动我们64位版本的应用程序
	}
	else
	{
		_tprintf(L"This process on 64 operating System\n");
		//说明当前操作系统是32位。
		//启动我们32位版本的应用程序
	}


	_gettchar();
	return 0;
}

