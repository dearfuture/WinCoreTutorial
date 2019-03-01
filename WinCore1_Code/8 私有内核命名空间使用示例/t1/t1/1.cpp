#include<Windows.h>
#include<tchar.h>
#include"resource.h"
#include<Sddl.h>
#include<Strsafe.h>

HANDLE h_Bundary;//�߽����������
HANDLE h_Namespace;//˽�������ռ���
HANDLE hMutex;//�ں˶�����
BOOL opened=FALSE;//ʹ��ClosePrivateNamespace����������˽�������ռ��ʱ����Ҫ֪��
//˽�������ռ��Ƿ��Ǳ����򴴽��ģ�����ǣ���ô���ClosePrivateNamespace�����ĵڶ�������
//Ϊ1������Ϊ0.


INT_PTR CALLBACK Dlg_pro(
  __in  HWND hwndDlg,
  __in  UINT uMsg,
  __in  WPARAM wParam,
  __in  LPARAM lParam
);

BOOL CheckInstance(HWND);

int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE,LPTSTR lpCmdLine,int nCmdShow)
{
	DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOG1),NULL,Dlg_pro);
	if(hMutex)
		CloseHandle(hMutex);//ɱ���ں˶���
	if(h_Namespace)//����˽�������ռ䡣
	{
		if(opened)
			ClosePrivateNamespace(h_Namespace,0);
			//����Ǵ�˽�������ռ䣬ClosePrivateNamespace�ĵڶ���������0

		else
			ClosePrivateNamespace(h_Namespace,1);
			//����Ǵ�����˽�������ռ䣬ClosePrivateNamespace�ĵڶ���������1
	}

	if(h_Bundary)
		DeleteBoundaryDescriptor(h_Bundary);//���ٱ߽�����������

	return 0;
}

INT_PTR CALLBACK Dlg_pro(
  __in  HWND hwndDlg,
  __in  UINT uMsg,
  __in  WPARAM wParam,
  __in  LPARAM lParam
)
{
	if(uMsg==WM_INITDIALOG)//��ʼ���Ի�����Ϣ
	{
		SetDlgItemText(hwndDlg,IDC_STATIC1,L"");//����̬�ı����е�������ա�
		CheckInstance(hwndDlg);//�����ļ�麯��
	}
	if(uMsg==WM_COMMAND)//�˳���Ϣ
	{
		if(HIWORD(wParam)==BN_CLICKED&&LOWORD(wParam)==IDCANCEL)
			EndDialog(hwndDlg,0);
	}

	return  0;
}

BOOL CheckInstance(HWND hwnd)
{
	
	h_Bundary=CreateBoundaryDescriptor(L"ydm",0);//����һ���߽���������
	BYTE LocalAdmiSID[SECURITY_MAX_SID_SIZE];
	DWORD cbSID=sizeof(LocalAdmiSID);
	CreateWellKnownSid(WinBuiltinAdministratorsSid,NULL,&LocalAdmiSID,&cbSID);
	//����һ������ԱSID
	AddSIDToBoundaryDescriptor(&h_Bundary,&LocalAdmiSID);
	//������ԱSID���뵽�߽��������У��˺�ֻ�й���Ա���ܹ�������߽���������Ӧ��˽�������ռ䣡

	SECURITY_ATTRIBUTES sa;
	sa.nLength=sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle=FALSE;
	ConvertStringSecurityDescriptorToSecurityDescriptor(L"D:(A;;GA;;;BA)",SDDL_REVISION_1,
		&sa.lpSecurityDescriptor,NULL);//������һ����ȫ��������
	/*
	D:	������������ȫ����������DACL-discretionary Access Control list
	A	��ʾ�����ȫ��������һ������ȫ�������������D-deny����ô��ʾ�ܾ���ȫ������allow
	GA:	��ʾ���ʵ�Ȩ��������Ȩ�ޣ�
	BA:	�����˹���ԱSID

	���"D:(A;;GA;;;BA)"�ַ����ǰ��գ�Security Descriptor Definition Language���ԣ�����д�ġ�
	*/
	
	h_Namespace=CreatePrivateNamespace(&sa,h_Bundary,L"ygg");
	//����˽�������ռ䣡����ע�⣬���һ������ֻ����������ռ�ı���������
	if(GetLastError()==ERROR_ALREADY_EXISTS)//���˽�������ռ��Ѿ���������ô���Ǵ����˽�������ռ䣡
	{
		h_Namespace=OpenPrivateNamespace(h_Bundary,L"ygg");
		//��˽�������ռ�
		opened=TRUE;//���ô򿪱�־������ClosePrivateNamespace�������һ�����������ã�
	}

	LocalFree(sa.lpSecurityDescriptor);
	//ConvertStringSecurityDescriptorToSecurityDescriptor���������Զ����������İ�ȫ�����������ڴ�
	//�������ȫ����������ʹ��ʱ��ʹ��LocalFree�����ͷ�����
	TCHAR szMutex[64];

	StringCchPrintf(szMutex,_countof(szMutex),L"%s\\%s",L"ygg",L"mutex");
	//�γ�һ��L"ygg\\mutex"�ַ�����
	
	hMutex=CreateMutex(NULL,FALSE,szMutex);//��ygg�����ռ��У�����һ�������ں˶���

	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{
		SetDlgItemText(hwnd,IDC_STATIC1,L"�Ѿ�����һ������");
	}
	else
	{
		SetDlgItemText(hwnd,IDC_STATIC1,L"���ǵ�һ������ʵ��");
	}

	return TRUE;
}