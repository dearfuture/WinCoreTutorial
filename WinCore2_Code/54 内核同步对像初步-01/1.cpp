/*
�ں�ͬ������

1. ����1����һ���ļ������ļ���д�����ݣ���ô����2���ڽ���1����������ļ���д�����ݺ󣬽���2�ڶ�ȡ����ļ��е����ݡ�

�¼��ں˶���

1.1 �������ں˶���hEvent��
1.2 �����ļ���д�����ݣ�
1.3 ���ں˶���hEvent���õ����ź�״̬��



2.1 �������ں˶���hEvent��
2.2 �ȴ��ں˶������źţ�
2.3 ���ļ�����ȡ���ݡ�

*/


#include<Windows.h>
#include<tchar.h>

TCHAR str[0x100]=L"abc";


int main()
{
	DWORD dwBytes;
	HANDLE hEvent=CreateEvent(NULL,FALSE,FALSE,L"ydm");

	_tprintf(L"GetLastError = %d\n",GetLastError());

	HANDLE hFile=CreateFile(L"E:\\test\\1.x",GENERIC_ALL,0,NULL,CREATE_ALWAYS,0,NULL);

	WriteFile(hFile,str,0x100*2,&dwBytes,NULL);

	CloseHandle(hFile);

	SetEvent(hEvent);


	_gettchar();
	return 0;

}