#include<Windows.h>
#include<tchar.h>


int _tmain()
{
	TCHAR** p=_wenviron;//����һ��ָ���ַ��������ָ�룻
	while(*p!=NULL)
	{
		_tprintf(L"%s\n",*p);
		p++;
	}
	_gettchar();
	return 0;
}