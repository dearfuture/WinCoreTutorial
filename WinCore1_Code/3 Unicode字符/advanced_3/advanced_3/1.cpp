//�ڿ���̨�����У���Ҫʹ��UNICODE�ַ����������ģ�������
#define UNICODE
#define _UNICODE
#include<Windows.h>
#include<stdio.h>
#include<tchar.h>
#include<Strsafe.h>

int wmain()
{
	char a=65;
	char *bb;
	wchar_t b;//�����ֽڣ������ı������˵��

	TCHAR s;//TCHAR�ڶ�����UNICODE��ʱ�򣬱�ʾwchar_t;
	//���û�ж���UNICODE��ôTCHAR�ʹ���char��
	//char* str="���ë";//��ʱ����ʵҲ��2���ֽڣ���ʾһ�����֡�
	//str="yangdamao"
	TCHAR mem[1000];

	printf("%d\n",sizeof(s));
	TCHAR *str=TEXT("���ë");//=��L"���ë"
	
	CreateWindow(L"abc",L"abc",NULL,0,0,0,0,NULL,0,NULL,0);

	wprintf(L"%S\n",str);
	printf("%s\n","���ë");//strlen

	printf("%d\n",_tcslen(TEXT("abc")));

	//strcpy(bb,"abc");

	StringCchPrintf(mem,1000,L"%d,%s",100,L"this is test");
	printf("%d,%s\n",100,"this is test");


	if(IsTextUnicode("abc",3,NULL))
		printf("this is unicode\n");
	else
		printf("this is ASCII\n");

	getchar();
	return 0;

}

