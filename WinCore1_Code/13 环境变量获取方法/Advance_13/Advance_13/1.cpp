#include<Windows.h>
#include<stdio.h>

//extern char **_environ;


int main()
{
	char** p=_environ;//����һ��ָ���ַ��������ָ�룻
	while(*p!=NULL)
	{
		printf("%s\n",*p);
		p++;
	}
	getchar();
	return 0;
}
