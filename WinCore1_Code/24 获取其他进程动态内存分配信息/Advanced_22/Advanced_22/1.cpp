#include<Windows.h>
#include<tchar.h>
#include<Tlhelp32.h>

int _tmain()
{
	int i=2000;//自动变量，这个变量，放在那里呢？放在线程栈里面。

	while(1)
	{

		_tprintf(L"%d\n",i);
	}


	_gettchar();
	return 0;

}