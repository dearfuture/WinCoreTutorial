#include<Windows.h>
#include<tchar.h>




int _tmain()
{
	TCHAR* p=GetEnvironmentStrings();

	while(*p!=0)
	{
		_tprintf(L"%s\n",p);
		p=p+_tcslen(p)+1;
	}

	_gettchar();
	return 0;
}