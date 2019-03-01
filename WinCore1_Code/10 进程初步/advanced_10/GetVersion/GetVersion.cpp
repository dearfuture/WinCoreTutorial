#include <windows.h>
#include <stdio.h>

void main()
{
    DWORD dwVersion = 0; 
    DWORD dwMajorVersion = 0;
    DWORD dwMinorVersion = 0; 
    DWORD dwBuild = 0;

    dwVersion = GetVersion();

	printf("%0x\n",dwVersion);
 
    // Get the Windows version.
	//һ���Ӿ���WORD��
	WORD Version=LOWORD(dwVersion);
	//dwVersion�У����λ�֣�
    dwMajorVersion = (DWORD)(LOBYTE(Version));
	//Version�ֵĵ��ֽڴ����汾��
    dwMinorVersion = (DWORD)(HIBYTE(Version));
	//Version�ֵĸ��ֽڴ���С�汾��

    // Get the build number.

    if (dwVersion < 0x80000000)              
        dwBuild = (DWORD)(HIWORD(dwVersion));
	//dwVersion�ĸ�λ�֣���ʾbuild�š�

    printf("Version is %d.%d (%d)\n", 
                dwMajorVersion,
                dwMinorVersion,
                dwBuild);

	getchar();
}

