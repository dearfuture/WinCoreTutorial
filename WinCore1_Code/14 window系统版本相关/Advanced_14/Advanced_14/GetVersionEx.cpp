#include<Windows.h>
#include<tchar.h>

int _tmain()
{

	OSVERSIONINFOEX infoEx;
	ZeroMemory(&infoEx,sizeof(OSVERSIONINFOEX));
	infoEx.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX);
	GetVersionEx((LPOSVERSIONINFO)&infoEx);

	_tprintf(L"%d\t%d\t%d\t%d\t%d\t%d\n",
		infoEx.dwMajorVersion,
		infoEx.dwMinorVersion,
		infoEx.dwBuildNumber,
		infoEx.dwPlatformId,
		infoEx.wServicePackMajor,
		infoEx.wServicePackMinor);



	_gettchar();
	return 0;
}
