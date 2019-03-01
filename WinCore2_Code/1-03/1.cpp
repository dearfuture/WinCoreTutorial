#include<Windows.h>
#include<tchar.h>

/*
1. �ж�һ�������Ƿ���ĳ��JOb�� IsProcessInJob
2. ����һ����ҵ���� CreateJobObject
3. �ѽ��̷ŵ�һ����ҵ�����У�AssignProcessToJobObject
*/

/*
����Ҫ����ҵ�еĽ���ʩ��һЩ���ƻ���˵���ƣ���ô����Ҫһ��������SetInformationJobObject

BOOL WINAPI SetInformationJobObject(
__in  HANDLE hJob,
__in  JOBOBJECTINFOCLASS JobObjectInfoClass,
__in  LPVOID lpJobObjectInfo,
__in  DWORD cbJobObjectInfoLength
);

hJob:				������Ҫ���Ǹ���ҵ�������������������ô������Ǹ���ҵ�ľ����
JobObjectInfoClass:	����Ҫ����ҵ���������һ���������������������һ��ö�٣����ǿ�ѡ��ö�����£�
	JobObjectBasicLimitInformation-2				JOBOBJECT_BASIC_LIMIT_INFORMATION
	JobObjectBasicUIRestrictions-4					JOBOBJECT_BASIC_UI_RESTRICTIONS 
	JobObjectSecurityLimitInformation-5				JOBOBJECT_SECURITY_LIMIT_INFORMATION 
	JobObjectEndOfJobTimeInformation-6				JOBOBJECT_END_OF_JOB_TIME_INFORMATION 
	JobObjectAssociateCompletionPortInformation-7	JOBOBJECT_ASSOCIATE_COMPLETION_PORT 
	JobObjectGroupInformation-11					�������ǵļ��ü����������ֻ��һ����Ⱥ0��


lpJobObjectInfo:	����Ҫʩ�ӵľ������ƣ��ͱ�������������У�����JobObjectInfoClass����ȡֵ�Ĳ�ͨ�����ָ��
					ָ��ͨ�Ľṹ�塣


cbJobObjectInfoLength:	����������ָ����ڴ��Ĵ�С��Bytes

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


	LimitFlags:	���������˵���˽ṹ���У��Ǹ�������Ҫ�����ã�

	
	
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