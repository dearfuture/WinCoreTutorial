#include<Windows.h>
#include<tchar.h>

int _tmain()
{
	TCHAR szPath[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,szPath);

	_tprintf(TEXT("%s\n"),szPath);

	TCHAR* str=L"D:\\ydm";//  ��\�����ַ����н�ת�����

	SetCurrentDirectory(str);


	GetCurrentDirectory(MAX_PATH,szPath);

	_tprintf(TEXT("%s\n"),szPath);

	

	if(!GetFullPathName(L"zhongguoren",MAX_PATH,szPath,NULL))//���������˵�˵���
		_tprintf(L"GetFullPathName is fail!\n");
	_tprintf(TEXT("%s\n"),szPath);


	_gettchar();
	return 0;
}
