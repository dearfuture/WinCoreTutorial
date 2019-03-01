//在控制台程序中，不要使用UNICODE字符，会出问题的！！！！
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
	wchar_t b;//两个字节！！核心编程书上说，

	TCHAR s;//TCHAR在定义了UNICODE的时候，表示wchar_t;
	//如果没有定义UNICODE那么TCHAR就代表char。
	//char* str="杨大毛";//此时，其实也是2个字节，表示一个汉字。
	//str="yangdamao"
	TCHAR mem[1000];

	printf("%d\n",sizeof(s));
	TCHAR *str=TEXT("杨大毛");//=》L"杨大毛"
	
	CreateWindow(L"abc",L"abc",NULL,0,0,0,0,NULL,0,NULL,0);

	wprintf(L"%S\n",str);
	printf("%s\n","杨大毛");//strlen

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

