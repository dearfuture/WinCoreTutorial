#include<Windows.h>
#include<tchar.h>


extern "C" HANDLE __ImageBase;//这应该是一个为变量，他的地址代表当前模块的其实地址，也可以看作是模块的句柄。
int _tWinMain(HINSTANCE hInstance,HINSTANCE,TCHAR*,int)
{
	//windows程序中，一般都会有Kernel32.dll这个模块，那么现在我们就获得这个模块的句柄；
	HMODULE hModule=GetModuleHandle(L"Kernel32.dll");

	_tprintf(L"%0x\n",hModule);

	
	//CloseHandle(hModule);模块句柄不要释放！！！

	//如何获得当前进程句柄。
	HMODULE hCurrent_Module=GetModuleHandle(NULL);//这个句柄，就是当前程序的起始地址。
	_tprintf(L"%0x\n",hCurrent_Module);



	TCHAR filename[MAX_PATH];
	GetModuleFileName(hCurrent_Module,filename,MAX_PATH);

	_tprintf(L"%s\n",filename);

	GetModuleFileName(hModule,filename,MAX_PATH);

	_tprintf(L"%s\n",filename);



	_tprintf(L"%0x\n",&__ImageBase);



	_gettchar();
	return 0;
}
