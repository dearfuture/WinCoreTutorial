#include<Windows.h>
#include<tchar.h>


int _tmain()
{
	TCHAR** p=_wenviron;//这是一个指向字符串数组的指针；
	while(*p!=NULL)
	{
		_tprintf(L"%s\n",*p);
		p++;
	}
	_gettchar();
	return 0;
}