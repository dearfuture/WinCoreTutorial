#include<Windows.h>
#include<tchar.h>

class A
{
public:
	A()
	{
		_tprintf(L"Constructor!\n");
	}
	~A()
	{
		_tprintf(L"Destructor!\n");
	}
};

int _tmain()
{
	_tprintf(L"this is Advanced_17 process\n");
	{
		A a;
		//ExitProcess(0);//����ֱ���˳��Ļ���C++���ٺ������������ã����ԣ�����������Ƽ�ʹ�á�
		goto LL;
	}
	_tprintf(L"press any key to exit Advanced_17 process\n");

	_gettchar();
LL:
	return 0;
}

