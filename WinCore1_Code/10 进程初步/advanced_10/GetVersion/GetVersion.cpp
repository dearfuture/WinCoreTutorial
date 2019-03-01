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
	//一个子就是WORD；
	WORD Version=LOWORD(dwVersion);
	//dwVersion中，其地位字，
    dwMajorVersion = (DWORD)(LOBYTE(Version));
	//Version字的低字节代表大版本号
    dwMinorVersion = (DWORD)(HIBYTE(Version));
	//Version字的高字节代表小版本号

    // Get the build number.

    if (dwVersion < 0x80000000)              
        dwBuild = (DWORD)(HIWORD(dwVersion));
	//dwVersion的高位字，表示build号。

    printf("Version is %d.%d (%d)\n", 
                dwMajorVersion,
                dwMinorVersion,
                dwBuild);

	getchar();
}

