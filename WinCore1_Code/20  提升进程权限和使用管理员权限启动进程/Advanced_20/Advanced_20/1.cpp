#include<Windows.h>
#include<tchar.h>


//���������������Ȩ�������ɾ��е���Ȩ�޵Ľ��̣����Ȩ��Ӧ���ǽ���
//���ܾ��е����Ȩ�ޡ�
//��������ɹ���ǰ�ᣬ�����ǣ�����������̵��ʺű����ǹ���Ա�ʺš�
//��fEnable=TRUE��ʱ�����赱ǰ���̵���Ȩ��
//��fEnable=FALSE��ʱ��ȡ����ǰ���̵���Ȩ�ޡ�

//����������TRUEʱ��˵��Ȩ�޵����ɹ�������ʧ�ܡ�
BOOL EnableDebugPrivilege(BOOL fEnable) 
{
   //����Ȩ�޿����øý����ܹ���ȡ�������̵���Ϣ��
   BOOL fOk = FALSE;    // Assume function fails
   HANDLE hToken;

   // ��ȡ��ǰ���̵����ƣ�
   //���������һ�������ǵ�ǰ���̾�����ڶ��������ǣ����̶Ի�õ����ƣ�����Щ����
   //Ȩ�ޡ�
   if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, 
      &hToken)) {

      //��ʼ���ǰ���Ƶĵ���Ȩ�ޡ�
      TOKEN_PRIVILEGES tp;//�ṹ�壬��ʾ����Ȩ��
	  /*
	  typedef struct _TOKEN_PRIVILEGES {
		DWORD               PrivilegeCount;
		//����ṹ�壬�м���Ȩ�ޣ�Ҳ���ǵڶ�����Ա����Privaileges���飬�м���Ԫ�ء�
		LUID_AND_ATTRIBUTES Privileges[ANYSIZE_ARRAY];
		} TOKEN_PRIVILEGES, *PTOKEN_PRIVILEGES;
		
		typedef struct _LUID_AND_ATTRIBUTES {
			LUID  Luid;//����Ψһ��ʶ�����������ظ���һ�����顣���������GUID��һ������
			DWORD Attributes;//Ȩ�����ԡ�
		} LUID_AND_ATTRIBUTES, *PLUID_AND_ATTRIBUTES;


	  */
      tp.PrivilegeCount = 1;//��ʱ����ֵ��������Ȩ�ޣ�������1
	  //����һ�����������ҵ���Ȩ�޵�LUID�������һ��������NULL����ʾ��ȡ����
	  //��ĳ��Ȩ�޵�LUID
      LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
	  //�����LookupPrivilegeValue��������ȡ����ϵͳ�ĵ���Ȩ�޵�LUID��

	  //����һ�仰����tp.Privileges[0].Attributes�����У������ǿ������Ȩ�ޣ�����
	  //�ر����Ȩ�ޡ�
      tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;
	  //��Attributes=SE_PRIVILEGE_ENABLEʱ������Ȩ��
	  //��Attributes=0ʱ���ر�Ȩ�ޡ�
      AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
	  //AdjustTokenPrivileges������߹ر�tp�и�����Ȩ�ޡ�
      fOk = (GetLastError() == ERROR_SUCCESS);//ȷʵ�����Ƿ�ɹ���
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
	ShExecInfo.lpVerb = L"runas"; //����������ã�������ShellExecuteEx����
	//�����Ľ��̣���Ҫʹ�ù������ơ�
	ShExecInfo.lpFile = L"cmd";  //���������Ҫ�����ĳ���
	ShExecInfo.lpParameters = L"";  
	ShExecInfo.lpDirectory = NULL;  
	ShExecInfo.nShow = SW_SHOW; //���������������ã���ô�㿴���������������
	//���ڡ�
	ShExecInfo.hInstApp = NULL;  
	ShellExecuteEx(&ShExecInfo);  

	return 0;
}