#include<Windows.h>
#include<tchar.h>

int _tWinMain(HINSTANCE,HINSTANCE,TCHAR* CommandLine,int)
{
	TCHAR* pTemp;
	_tprintf(L"%s\n",CommandLine);//CommandLine�����������г������

	pTemp=GetCommandLine();

	/*
	���������ʱ��õ��������ַ�����������ִ�г�������ֺͲ��������Ǳ��ŵ�һ���ַ����У�

	ע�⣺��ִ�г�������֣��������������ˡ�


	*/

	return 0;
}