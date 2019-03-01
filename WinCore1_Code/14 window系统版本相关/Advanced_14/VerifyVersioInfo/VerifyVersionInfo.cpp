#include<Windows.h>
#include<tchar.h>

int _tmain()
{

	OSVERSIONINFOEX infoEx;
	ZeroMemory(&infoEx,sizeof(OSVERSIONINFOEX));
	infoEx.dwOSVersionInfoSize=sizeof(OSVERSIONINFOEX);

	infoEx.dwMajorVersion=6;
	infoEx.dwMinorVersion=2;
	infoEx.wServicePackMajor=0;
	infoEx.wServicePackMinor=0;

	DWORDLONG dwlConditionMask=0;

	VER_SET_CONDITION(dwlConditionMask,VER_MAJORVERSION,VER_GREATER_EQUAL);
	VER_SET_CONDITION(dwlConditionMask,VER_MINORVERSION,VER_GREATER_EQUAL);
	VER_SET_CONDITION(dwlConditionMask,VER_SERVICEPACKMAJOR,VER_GREATER_EQUAL);
	VER_SET_CONDITION(dwlConditionMask,VER_SERVICEPACKMINOR,VER_GREATER_EQUAL);

	DWORD dwTypeMask=VER_MAJORVERSION|VER_MINORVERSION|
		VER_SERVICEPACKMAJOR|VER_SERVICEPACKMINOR;


	if(VerifyVersionInfo(&infoEx,dwTypeMask,dwlConditionMask))
	{
		_tprintf(L"this system is sufficient!\n");
	}
	else
	{
		_tprintf(L"this system is not ok\n");
	}
	_gettchar();
	return 0;
}



