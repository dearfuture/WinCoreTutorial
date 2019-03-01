#include<Windows.h>
#include<stdio.h>

//extern char **_environ;


int main()
{
	char** p=_environ;//这是一个指向字符串数组的指针；
	while(*p!=NULL)
	{
		printf("%s\n",*p);
		p++;
	}
	getchar();
	return 0;
}
