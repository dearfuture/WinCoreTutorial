#include<Windows.h>
#include<tchar.h>

int _tmain(int argc,TCHAR* argv[])
{
	for(int i=0;i<argc;i++)
	{
		_tprintf(L"%s\n",argv[i]);
	}

	_gettchar();
	return 0;
}