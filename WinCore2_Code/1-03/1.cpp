#include<Windows.h>
#include<tchar.h>

/*
1. 判断一个进程是否在某个JOb内 IsProcessInJob
2. 创建一个作业对象： CreateJobObject
3. 把进程放到一个作业对象中：AssignProcessToJobObject
*/

/*
我们要给作业中的进程施加一些限制或者说控制，那么就需要一个函数：SetInformationJobObject

BOOL WINAPI SetInformationJobObject(
__in  HANDLE hJob,
__in  JOBOBJECTINFOCLASS JobObjectInfoClass,
__in  LPVOID lpJobObjectInfo,
__in  DWORD cbJobObjectInfoLength
);

hJob:				我们需要给那个作业对象添加限制条件，那么这就是那个作业的句柄。
JobObjectInfoClass:	我们要给作业对象添加哪一类限制条件，这个参数是一个枚举，我们可选的枚举如下：
	JobObjectBasicLimitInformation-2				JOBOBJECT_BASIC_LIMIT_INFORMATION
	JobObjectBasicUIRestrictions-4					JOBOBJECT_BASIC_UI_RESTRICTIONS 
	JobObjectSecurityLimitInformation-5				JOBOBJECT_SECURITY_LIMIT_INFORMATION 
	JobObjectEndOfJobTimeInformation-6				JOBOBJECT_END_OF_JOB_TIME_INFORMATION 
	JobObjectAssociateCompletionPortInformation-7	JOBOBJECT_ASSOCIATE_COMPLETION_PORT 
	JobObjectGroupInformation-11					现在我们的家用计算机基本上只有一个组群0。


lpJobObjectInfo:	我们要施加的具体限制，就保存在这个参数中，根据JobObjectInfoClass参数取值的不通，这个指针
					指向不通的结构体。


cbJobObjectInfoLength:	第三个参数指向的内存块的大小。Bytes

*/


int main()
{
	HANDLE hJob=CreateJobObject(NULL, NULL);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	SYSTEMTIME time;
	GetSystemTime(&time);

	_tprintf(L"%d:%d\n", time.wMinute, time.wSecond);

	BOOL re = CreateProcess(L"C:\\Users\\Administrator\\Desktop\\TSTCON32.EXE",   // No module name (use command line)
		NULL,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi);           // Pointer to PROCESS_INFORMATION structure

	
	re=AssignProcessToJobObject(hJob, pi.hProcess);
	if (re)
		_tprintf(L"AssingProcessToJobObject OK!\n");

	JOBOBJECT_BASIC_LIMIT_INFORMATION info = { 0 };
	/*
	typedef struct _JOBOBJECT_BASIC_LIMIT_INFORMATION {
	LARGE_INTEGER PerProcessUserTimeLimit;
	LARGE_INTEGER PerJobUserTimeLimit;
	DWORD         LimitFlags;
	SIZE_T        MinimumWorkingSetSize;
	SIZE_T        MaximumWorkingSetSize;
	DWORD         ActiveProcessLimit;
	ULONG_PTR     Affinity;
	DWORD         PriorityClass;
	DWORD         SchedulingClass;
	} JOBOBJECT_BASIC_LIMIT_INFORMATION, *PJOBOBJECT_BASIC_LIMIT_INFORMATION;


	LimitFlags:	这个参数，说明了结构体中，那个参数将要被设置！

	
	
	*/
	
	info.LimitFlags = JOB_OBJECT_LIMIT_PROCESS_TIME;

	LARGE_INTEGER t;
	t.QuadPart = 10;
	info.PerProcessUserTimeLimit = t;

	
	


	re=SetInformationJobObject(hJob, JobObjectBasicLimitInformation, &info, sizeof(info));
	if (!re)
	{
		_tprintf(L"SetInformationJobObject errno=%d\n", GetLastError());
	}


	info.LimitFlags = JOB_OBJECT_LIMIT_JOB_TIME;
	t.QuadPart = 10;
	info.PerJobUserTimeLimit = t;

	re = SetInformationJobObject(hJob, JobObjectBasicLimitInformation, &info, sizeof(info));
	if (!re)
	{
		_tprintf(L"SetInformationJobObject errno=%d\n", GetLastError());
	}

	//_gettchar();
	CloseHandle(hJob);
	
	WaitForSingleObject(pi.hProcess, INFINITE);

	GetSystemTime(&time);

	_tprintf(L"%d:%d\n", time.wMinute, time.wSecond);
	_gettchar();

	return 0;

}