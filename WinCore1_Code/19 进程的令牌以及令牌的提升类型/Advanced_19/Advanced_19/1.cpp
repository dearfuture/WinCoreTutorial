#include<Windows.h>
#include<tchar.h>
#include<Shlobj.h>

//可以把这个函数当Windows API来用。这个函数返回BOOL，当函数返回TRUE的时候，函数成功，当函数返回FALSE的话
//函数失败。

/*
TOKEN_ELEVATION_TYPE* pElevationType：令牌提升类型。
BOOL* pIsAdmin ：是否是管理员。保存结果

这个函数，确定了，运行当前程序的帐号，是否为管理员帐号，以及当前进程的令牌，是那种令牌。甚至你还可以确定，当前
的这个操作系统是否启动了UAC功能。
*/
BOOL GetProcessElevation(TOKEN_ELEVATION_TYPE* pElevationType, BOOL* pIsAdmin) 
{
   HANDLE hToken = NULL;
   DWORD dwSize;

   // 获得当前进程的令牌句柄。
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
      return(FALSE);

   BOOL bResult = FALSE;

   // 看看这个令牌的权限提升类型是哪一种：
   /*
		TokenElevationTypeDefault：进程以缺省的用户身份运行，或者没有使用UAC功能，简单来说，就是用户没有启动UAC功能，那么程序使用的令牌，一定不是Filter Token。

		TokenElevationTypeFull：进程的权限已经被提升，进程令牌没有使用filter令牌

		TokenElevationTypeLimited：进程使用的令牌是Filter令牌。此时通过GetTokenInformation函数，并使用TokenLinkedToken标志，来获取原令牌。

	*/
   if (GetTokenInformation(hToken, TokenElevationType,
      pElevationType, sizeof(TOKEN_ELEVATION_TYPE), &dwSize)) 
   {
      // 创建一个管理员SID
      BYTE adminSID[SECURITY_MAX_SID_SIZE];
      dwSize = sizeof(adminSID);
      CreateWellKnownSid(WinBuiltinAdministratorsSid, NULL, &adminSID,
         &dwSize);

      if (*pElevationType == TokenElevationTypeLimited) 
	  {
         //通过Filter Token来获得原始的Token
         HANDLE hUnfilteredToken = NULL;
		 //TokenLinkedToken标志，表示要获得Filter Token的原始Token。
         GetTokenInformation(hToken, TokenLinkedToken, (VOID*)
            &hUnfilteredToken, sizeof(HANDLE), &dwSize);

         // 检查原始Token中，管理员账户adminSID是否被激活，如果被激活，那么说明启动这个
		 //程序的帐号是管理员帐号，否则不是。
         if (CheckTokenMembership(hUnfilteredToken, &adminSID, pIsAdmin)) 
			//这个CheckTokenMembership函数，结果被保存在pIsAdmin参数中，而这个函数的返回值
			//只是表示，这个函数是否成功。
		 {
            bResult = TRUE;
         }

         // 不要忘了关闭原始令牌。
         CloseHandle(hUnfilteredToken);
      } 
	  else //如果是原始令牌，只要IsUsrAndmin就可以确定，启动当前程序的帐号是否是管理员帐号。
	  {
         *pIsAdmin = IsUserAnAdmin();
         bResult = TRUE;
      }
   }

   // 不要忘了关闭进程令牌。
   CloseHandle(hToken);
   return(bResult);
}


int _tmain()
{
	TOKEN_ELEVATION_TYPE Type;
	BOOL IsAdmin;

	BOOL re=GetProcessElevation(&Type, &IsAdmin);

	if(re)
	{
		_tprintf(L"%d,Type");
		if(IsAdmin)
			_tprintf(L"on Admin running!\n");
		else
			_tprintf(L"on normal acount running!\n");

	}

	_gettchar();
	return 0;
}