#include<Windows.h>
#include<tchar.h>
#include"resource.h"
#include<Sddl.h>
#include<Strsafe.h>

HANDLE h_Bundary;//边界描述符句柄
HANDLE h_Namespace;//私有命名空间句柄
HANDLE hMutex;//内核对象句柄
BOOL opened=FALSE;//使用ClosePrivateNamespace函数，销毁私有命名空间的时候，需要知道
//私有命名空间是否是本程序创建的，如果是，那么这个ClosePrivateNamespace函数的第二个参数
//为1，否则为0.


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
		CloseHandle(hMutex);//杀死内核对象
	if(h_Namespace)//销毁私有命名空间。
	{
		if(opened)
			ClosePrivateNamespace(h_Namespace,0);
			//如果是打开私有命名空间，ClosePrivateNamespace的第二个参数是0

		else
			ClosePrivateNamespace(h_Namespace,1);
			//如果是创建的私有命名空间，ClosePrivateNamespace的第二个参数是1
	}

	if(h_Bundary)
		DeleteBoundaryDescriptor(h_Bundary);//销毁边界描述符！！

	return 0;
}

INT_PTR CALLBACK Dlg_pro(
  __in  HWND hwndDlg,
  __in  UINT uMsg,
  __in  WPARAM wParam,
  __in  LPARAM lParam
)
{
	if(uMsg==WM_INITDIALOG)//初始化对话框消息
	{
		SetDlgItemText(hwndDlg,IDC_STATIC1,L"");//将静态文本框中的内容清空。
		CheckInstance(hwndDlg);//真正的检查函数
	}
	if(uMsg==WM_COMMAND)//退出消息
	{
		if(HIWORD(wParam)==BN_CLICKED&&LOWORD(wParam)==IDCANCEL)
			EndDialog(hwndDlg,0);
	}

	return  0;
}

BOOL CheckInstance(HWND hwnd)
{
	
	h_Bundary=CreateBoundaryDescriptor(L"ydm",0);//创建一个边界描述符！
	BYTE LocalAdmiSID[SECURITY_MAX_SID_SIZE];
	DWORD cbSID=sizeof(LocalAdmiSID);
	CreateWellKnownSid(WinBuiltinAdministratorsSid,NULL,&LocalAdmiSID,&cbSID);
	//创建一个管理员SID
	AddSIDToBoundaryDescriptor(&h_Bundary,&LocalAdmiSID);
	//将管理员SID加入到边界描述符中，此后，只有管理员才能够打开这个边界描述符对应的私有命名空间！

	SECURITY_ATTRIBUTES sa;
	sa.nLength=sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle=FALSE;
	ConvertStringSecurityDescriptorToSecurityDescriptor(L"D:(A;;GA;;;BA)",SDDL_REVISION_1,
		&sa.lpSecurityDescriptor,NULL);//创建了一个安全描述符：
	/*
	D:	这个代表这个安全描述符中有DACL-discretionary Access Control list
	A	表示这个安全描述符是一个允许安全描述符，如果是D-deny，那么表示拒绝安全描述符allow
	GA:	表示访问的权限是所有权限；
	BA:	代表了管理员SID

	这个"D:(A;;GA;;;BA)"字符串是按照：Security Descriptor Definition Language语言，来编写的。
	*/
	
	h_Namespace=CreatePrivateNamespace(&sa,h_Bundary,L"ygg");
	//创建私有命名空间！！！注意，最后一个参数只是这个命名空间的别名！！！
	if(GetLastError()==ERROR_ALREADY_EXISTS)//如果私有命名空间已经创建，那么我们打开这个私有命名空间！
	{
		h_Namespace=OpenPrivateNamespace(h_Bundary,L"ygg");
		//打开私有命名空间
		opened=TRUE;//设置打开标志，用于ClosePrivateNamespace函数最后一个参数的设置！
	}

	LocalFree(sa.lpSecurityDescriptor);
	//ConvertStringSecurityDescriptorToSecurityDescriptor函数，会自动给被创建的安全描述符分配内存
	//当这个安全描述符不再使用时，使用LocalFree函数释放他。
	TCHAR szMutex[64];

	StringCchPrintf(szMutex,_countof(szMutex),L"%s\\%s",L"ygg",L"mutex");
	//形成一个L"ygg\\mutex"字符串！
	
	hMutex=CreateMutex(NULL,FALSE,szMutex);//在ygg命名空间中，创建一个互斥内核对象！

	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{
		SetDlgItemText(hwnd,IDC_STATIC1,L"已经存在一个程序");
	}
	else
	{
		SetDlgItemText(hwnd,IDC_STATIC1,L"这是第一个程序实例");
	}

	return TRUE;
}