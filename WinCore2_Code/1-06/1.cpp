#include<Windows.h>
#include<tchar.h>

/*
typedef struct _JOBOBJECT_EXTENDED_LIMIT_INFORMATION {
JOBOBJECT_BASIC_LIMIT_INFORMATION BasicLimitInformation;
IO_COUNTERS                       IoInfo;
SIZE_T                            ProcessMemoryLimit;
SIZE_T                            JobMemoryLimit;
SIZE_T                            PeakProcessMemoryUsed;
SIZE_T                            PeakJobMemoryUsed;
} JOBOBJECT_EXTENDED_LIMIT_INFORMATION, *PJOBOBJECT_EXTENDED_LIMIT_INFORMATION;

����Ƚϼ򵥣���ҿ�һ�¶������ˣ�

LimitFlags���������˵��������Ҫ������һ��������ֵ��
*/


/*

typedef struct _JOBOBJECT_BASIC_UI_RESTRICTIONS {
DWORD UIRestrictionsClass;
} JOBOBJECT_BASIC_UI_RESTRICTIONS, *PJOBOBJECT_BASIC_UI_RESTRICTIONS;

����������費ͬ��ֵ���������ͬ�����ơ�

JOB_OBJECT_UILIMIT_DESKTOP�� ��ҵ�еĽ��̣������ٴ�������



*/




/*

int _tmain()
{
	HANDLE hJob = CreateJobObject(NULL, L"ydm");

	JOBOBJECT_BASIC_UI_RESTRICTIONS info = { 0 };
	info.UIRestrictionsClass = JOB_OBJECT_UILIMIT_DESKTOP;

	AssignProcessToJobObject(hJob, GetCurrentProcess());
	SetInformationJobObject(hJob, JobObjectBasicUIRestrictions, &info, sizeof(info));


	HDESK hDesk = CreateDesktop(L"ydm", NULL, NULL, 0, GENERIC_ALL, NULL);

	HDESK hDesk_old = GetThreadDesktop(GetCurrentThreadId());

	SwitchDesktop(hDesk);
	SetThreadDesktop(hDesk);

	MessageBox(NULL, L"abc", L"abc", 0);

	SwitchDesktop(hDesk_old);

	CloseDesktop(hDesk);



	_gettchar();
	return 0;
}

*/

BOOL CALLBACK EnumWindowsProc(
	__in  HWND hwnd,
	__in  LPARAM lParam
	)
{
	_tprintf(L"%d\n", hwnd);
	return TRUE;

}




int _tmain()
{
	HANDLE hJob = CreateJobObject(NULL, L"ydm");

	JOBOBJECT_BASIC_UI_RESTRICTIONS info = { 0 };
	info.UIRestrictionsClass = JOB_OBJECT_UILIMIT_HANDLES;

	AssignProcessToJobObject(hJob, GetCurrentProcess());
	SetInformationJobObject(hJob, JobObjectBasicUIRestrictions, &info, sizeof(info));

	EnumWindows(EnumWindowsProc, 10);


	_gettchar();
	return 0;
}