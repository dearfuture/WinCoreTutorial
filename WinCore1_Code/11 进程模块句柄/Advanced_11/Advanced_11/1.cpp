#include<Windows.h>
#include<tchar.h>


extern "C" HANDLE __ImageBase;//��Ӧ����һ��Ϊ���������ĵ�ַ����ǰģ�����ʵ��ַ��Ҳ���Կ�����ģ��ľ����
int _tWinMain(HINSTANCE hInstance,HINSTANCE,TCHAR*,int)
{
	//windows�����У�һ�㶼����Kernel32.dll���ģ�飬��ô�������Ǿͻ�����ģ��ľ����
	HMODULE hModule=GetModuleHandle(L"Kernel32.dll");

	_tprintf(L"%0x\n",hModule);

	
	//CloseHandle(hModule);ģ������Ҫ�ͷţ�����

	//��λ�õ�ǰ���̾����
	HMODULE hCurrent_Module=GetModuleHandle(NULL);//�����������ǵ�ǰ�������ʼ��ַ��
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
