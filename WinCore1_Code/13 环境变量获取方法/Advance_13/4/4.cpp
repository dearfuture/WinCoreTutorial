#include<Windows.h>
#include<tchar.h>

int _tmain()
{
	DWORD length=ExpandEnvironmentStrings(L"%USERPROFILE%",NULL,0);
	//��һ�ε��������������Ϊ�˻�ģ�%USERPROFILE%����չ����ַ����Ĵ�С��
	TCHAR* str=new TCHAR[length+1];
	ExpandEnvironmentStrings(L"%USERPROFILE%",str,length);

	_tprintf(L"%s\n",str);


	_gettchar();
	return 0;
}
