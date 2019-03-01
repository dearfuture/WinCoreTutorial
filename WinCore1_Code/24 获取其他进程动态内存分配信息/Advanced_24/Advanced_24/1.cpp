
#include<Windows.h>
#include<tchar.h>
#include<Tlhelp32.h>

#define ID 23056

int _tmain()
{
	HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST,ID);
	if(hSnapshot==INVALID_HANDLE_VALUE)
	{
		_tprintf(L"%d\n",GetLastError());
		return 0;
	}

	HEAPLIST32 hl={0};
	hl.dwSize=sizeof(hl);
	Heap32ListFirst(hSnapshot,&hl);

	do
	{
		_tprintf(L"-------------------------------\n");
		_tprintf(TEXT("ProcessID=%d:HeapID=%d\n"),hl.th32ProcessID,hl.th32HeapID);
		HEAPENTRY32 he={0};
		he.dwSize=sizeof(he);
		Heap32First(&he,hl.th32ProcessID,hl.th32HeapID);
		do
		{
			_tprintf(TEXT("Address=%0X\tsize=%0X\tflages=%0X\n"),he.dwAddress,he.dwBlockSize,
				he.dwFlags);
		}while(Heap32Next(&he));

	}while(Heap32ListNext(hSnapshot,&hl));

	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,ID);

	
	int i=0;
	ReadProcessMemory(hProcess,(LPCVOID)(0X1AFA70),&i,4,NULL);

	i=0;
	WriteProcessMemory(hProcess,(LPVOID)(0X1AFA70),&i,4,NULL);


	CloseHandle(hSnapshot);
	CloseHandle(hProcess);
	_gettchar();
	return 0;
}

/*
这种列举方法，只能列举其他进程中的堆内存信息。
线程栈内的内存信息，没法列出来。

*/



/*
我们可以获得其他进程中内存数据，
也可以修改其他进程内存中的数据，
*/