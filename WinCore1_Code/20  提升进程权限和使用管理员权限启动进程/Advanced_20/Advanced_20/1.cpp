#include<Windows.h>
#include<tchar.h>


//这个函数，将进程权限提升成具有调试权限的进程，这个权限应该是进程
//所能具有的最大权限。
//这个函数成功的前提，必须是，启动这个进程的帐号必须是管理员帐号。
//当fEnable=TRUE的时候，授予当前进程调试权限
//当fEnable=FALSE的时候，取消当前进程调试权限。

//当函数返回TRUE时，说明权限调整成功，否则失败。
BOOL EnableDebugPrivilege(BOOL fEnable) 
{
   //调试权限可以让该进程能够读取其他进程的信息。
   BOOL fOk = FALSE;    // Assume function fails
   HANDLE hToken;

   // 获取当前进程的令牌！
   //这个函数第一个参数是当前进程句柄，第二个参数是：进程对获得的令牌，有那些操作
   //权限。
   if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, 
      &hToken)) {

      //开始激活当前令牌的调试权限。
      TOKEN_PRIVILEGES tp;//结构体，表示令牌权限
	  /*
	  typedef struct _TOKEN_PRIVILEGES {
		DWORD               PrivilegeCount;
		//这个结构体，有几个权限，也就是第二个成员变量Privaileges数组，有几个元素。
		LUID_AND_ATTRIBUTES Privileges[ANYSIZE_ARRAY];
		} TOKEN_PRIVILEGES, *PTOKEN_PRIVILEGES;
		
		typedef struct _LUID_AND_ATTRIBUTES {
			LUID  Luid;//本地唯一标识符。不肯能重复的一个数组。这个东西和GUID是一个东西
			DWORD Attributes;//权限属性。
		} LUID_AND_ATTRIBUTES, *PLUID_AND_ATTRIBUTES;


	  */
      tp.PrivilegeCount = 1;//此时我们值启动调试权限，所以是1
	  //下面一个函数，查找调试权限的LUID，如果第一个参数是NULL，表示获取本地
	  //的某个权限的LUID
      LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
	  //上面的LookupPrivilegeValue函数，获取本地系统的调试权限的LUID。

	  //下面一句话，在tp.Privileges[0].Attributes属性中，设置是开启这个权限，还是
	  //关闭这个权限。
      tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;
	  //当Attributes=SE_PRIVILEGE_ENABLE时，激活权限
	  //当Attributes=0时，关闭权限。
      AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
	  //AdjustTokenPrivileges激活或者关闭tp中给定的权限。
      fOk = (GetLastError() == ERROR_SUCCESS);//确实激活是否成功。
      CloseHandle(hToken);
   }
   return(fOk);
}

int _tWinMain(HINSTANCE,HINSTANCE,TCHAR*,int)
{


	if(EnableDebugPrivilege(TRUE))
	{
		_tprintf(L"Enable Debug privilege is ok!\n");
	}
	else
	{
		_tprintf(L"Enable Debug privilege is Failure!\n");
	}
	EnableDebugPrivilege(FALSE);


	//////////////////////////////////////////////
	SHELLEXECUTEINFO ShExecInfo = {0};  
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);  
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;  
	ShExecInfo.hwnd = NULL;  
	ShExecInfo.lpVerb = L"runas"; //这个参数设置，就是让ShellExecuteEx函数
	//启动的进程，不要使用过滤令牌。
	ShExecInfo.lpFile = L"cmd";  //这个就是你要启动的程序
	ShExecInfo.lpParameters = L"";  
	ShExecInfo.lpDirectory = NULL;  
	ShExecInfo.nShow = SW_SHOW; //如果这个参数不设置，那么你看不见被启动程序的
	//窗口。
	ShExecInfo.hInstApp = NULL;  
	ShellExecuteEx(&ShExecInfo);  

	return 0;
}