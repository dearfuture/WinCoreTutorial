#include<Windows.h>
#include<tchar.h>

int _tmain()
{
	TCHAR szPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,szPath);

	_tprintf(TEXT("%s\n"),szPath);

	TCHAR* str=L"D:\\ydm";//  “\”在字符串中叫转义符，

	SetCurrentDirectory(str);


	GetCurrentDirectory(MAX_PATH,szPath);

	_tprintf(TEXT("%s\n"),szPath);

	

	if(!GetFullPathName(L"zhongguoren",MAX_PATH,szPath,NULL))//这个函数胡说八道。
		_tprintf(L"GetFullPathName is fail!\n");
	_tprintf(TEXT("%s\n"),szPath);


	_gettchar();
	return 0;
}
