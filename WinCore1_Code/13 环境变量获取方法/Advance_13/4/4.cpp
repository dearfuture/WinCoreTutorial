#include<Windows.h>
#include<tchar.h>

int _tmain()
{
	DWORD length=ExpandEnvironmentStrings(L"%USERPROFILE%",NULL,0);
	//第一次调用这个函数，是为了会的，%USERPROFILE%被扩展后的字符串的大小。
	TCHAR* str=new TCHAR[length+1];
	ExpandEnvironmentStrings(L"%USERPROFILE%",str,length);

	_tprintf(L"%s\n",str);


	_gettchar();
	return 0;
}
