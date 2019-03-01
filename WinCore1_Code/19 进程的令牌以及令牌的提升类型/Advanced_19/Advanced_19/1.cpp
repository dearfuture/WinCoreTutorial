#include<Windows.h>
#include<tchar.h>
#include<Shlobj.h>

//���԰����������Windows API���á������������BOOL������������TRUE��ʱ�򣬺����ɹ�������������FALSE�Ļ�
//����ʧ�ܡ�

/*
TOKEN_ELEVATION_TYPE* pElevationType�������������͡�
BOOL* pIsAdmin ���Ƿ��ǹ���Ա��������

���������ȷ���ˣ����е�ǰ������ʺţ��Ƿ�Ϊ����Ա�ʺţ��Լ���ǰ���̵����ƣ����������ơ������㻹����ȷ������ǰ
���������ϵͳ�Ƿ�������UAC���ܡ�
*/
BOOL GetProcessElevation(TOKEN_ELEVATION_TYPE* pElevationType, BOOL* pIsAdmin) 
{
   HANDLE hToken = NULL;
   DWORD dwSize;

   // ��õ�ǰ���̵����ƾ����
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
      return(FALSE);

   BOOL bResult = FALSE;

   // ����������Ƶ�Ȩ��������������һ�֣�
   /*
		TokenElevationTypeDefault��������ȱʡ���û�������У�����û��ʹ��UAC���ܣ�����˵�������û�û������UAC���ܣ���ô����ʹ�õ����ƣ�һ������Filter Token��

		TokenElevationTypeFull�����̵�Ȩ���Ѿ�����������������û��ʹ��filter����

		TokenElevationTypeLimited������ʹ�õ�������Filter���ơ���ʱͨ��GetTokenInformation��������ʹ��TokenLinkedToken��־������ȡԭ���ơ�

	*/
   if (GetTokenInformation(hToken, TokenElevationType,
      pElevationType, sizeof(TOKEN_ELEVATION_TYPE), &dwSize)) 
   {
      // ����һ������ԱSID
      BYTE adminSID[SECURITY_MAX_SID_SIZE];
      dwSize = sizeof(adminSID);
      CreateWellKnownSid(WinBuiltinAdministratorsSid, NULL, &adminSID,
         &dwSize);

      if (*pElevationType == TokenElevationTypeLimited) 
	  {
         //ͨ��Filter Token�����ԭʼ��Token
         HANDLE hUnfilteredToken = NULL;
		 //TokenLinkedToken��־����ʾҪ���Filter Token��ԭʼToken��
         GetTokenInformation(hToken, TokenLinkedToken, (VOID*)
            &hUnfilteredToken, sizeof(HANDLE), &dwSize);

         // ���ԭʼToken�У�����Ա�˻�adminSID�Ƿ񱻼������������ô˵���������
		 //������ʺ��ǹ���Ա�ʺţ������ǡ�
         if (CheckTokenMembership(hUnfilteredToken, &adminSID, pIsAdmin)) 
			//���CheckTokenMembership�����������������pIsAdmin�����У�����������ķ���ֵ
			//ֻ�Ǳ�ʾ����������Ƿ�ɹ���
		 {
            bResult = TRUE;
         }

         // ��Ҫ���˹ر�ԭʼ���ơ�
         CloseHandle(hUnfilteredToken);
      } 
	  else //�����ԭʼ���ƣ�ֻҪIsUsrAndmin�Ϳ���ȷ����������ǰ������ʺ��Ƿ��ǹ���Ա�ʺš�
	  {
         *pIsAdmin = IsUserAnAdmin();
         bResult = TRUE;
      }
   }

   // ��Ҫ���˹رս������ơ�
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