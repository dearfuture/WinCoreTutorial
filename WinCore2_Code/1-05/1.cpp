#include<Windows.h>
#include<tchar.h>

BOOL WatchJob(HANDLE hJob, LPTHREAD_START_ROUTINE Proc);
DWORD WINAPI ThreadProc(LPVOID lParam);
/*

int _tmain()
{
	HANDLE hJob = CreateJobObject(NULL, L"ydm");
	

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcess(L"C:\\Users\\Administrator\\Desktop\\TSTCON32.EXE", NULL, NULL,
		NULL, FALSE, 0, NULL, NULL, &si, &pi);

	BOOL re=AssignProcessToJobObject(hJob, pi.hProcess);
	
	//........

	//������һЩ���ơ�
	


	//������Ҫ�鿴�ҵ���ҵ��ʩ������Щ���ƣ�

	JOBOBJECT_EXTENDED_LIMIT_INFORMATION info = { 0 };


	re=QueryInformationJobObject(hJob, JobObjectExtendedLimitInformation, &info,sizeof(info),NULL);



	return 0;
}
*/




/*


��ɶ˿ڣ�����ĳ�����Խ���Overlapped�������ں˶����ϵ��¼���
���ǿ��Լ��ӵ�����ҵ�е��¼���

JOB_OBJECT_MSG_ABNORMAL_EXIT_PROCESS 
	Indicates that a process associated with the job exited with an exit code that indicates an 
	abnormal exit (see the list following this table).The value of lpOverlapped is the identifier of the exiting process.

JOB_OBJECT_MSG_ACTIVE_PROCESS_LIMIT 
	Indicates that the active process limit has been exceeded.
	The value of lpOverlapped is NULL.

JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO 
	Indicates that the active process count has been decremented to 0. For example, 
	if the job currently has two active processes, the system sends this message after 
	they both terminate.
	The value of lpOverlapped is NULL.

JOB_OBJECT_MSG_END_OF_JOB_TIME 
	Indicates that the JOB_OBJECT_POST_AT_END_OF_JOB option is 
	in effect and the end-of-job time limit has been reached. 
	Upon posting this message, the time limit is canceled 
	and the job's processes can continue to run.
	The value of lpOverlapped is NULL.

JOB_OBJECT_MSG_END_OF_PROCESS_TIME 
	Indicates that a process has exceeded a per-process time limit. 
	The system sends this message after the process termination has been requested.
	The value of lpOverlapped is the identifier of the process that exceeded its limit.

JOB_OBJECT_MSG_EXIT_PROCESS 
	Indicates that a process associated with the job has exited.
	The value of lpOverlapped is the identifier of the exiting process.

JOB_OBJECT_MSG_JOB_MEMORY_LIMIT 
	Indicates that a process associated with the job caused 
	the job to exceed the job-wide memory limit (if one is in effect).
	The value of lpOverlapped specifies the identifier of the process 
	that has attempted to exceed the limit. The system does not send 
	this message if the process has not yet reported its process identifier.

JOB_OBJECT_MSG_NEW_PROCESS 
	Indicates that a process has been added to the job. Processes added 
	to a job at the time a completion port is associated are also reported.
	The value of lpOverlapped is the identifier of the process added to the job.

JOB_OBJECT_MSG_PROCESS_MEMORY_LIMIT 
	Indicates that a process associated with the job has exceeded 
	its memory limit (if one is in effect).
	The value of lpOverlapped is the identifier of the process 
	that has exceeded its limit. The system does not send this message if the process has not yet reported its process identifier.

*/

int _tmain()
{
	HANDLE hJob = CreateJobObject(NULL, L"ydm");


	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	CreateProcess(L"C:\\Users\\Administrator\\Desktop\\TSTCON32.EXE", NULL, NULL,
		NULL, FALSE, 0, NULL, NULL, &si, &pi);

	BOOL re = AssignProcessToJobObject(hJob, pi.hProcess);

	//........

	//������һЩ���ơ�



	//������Ҫ�鿴�ҵ���ҵ��ʩ������Щ���ƣ�

	JOBOBJECT_EXTENDED_LIMIT_INFORMATION info = { 0 };


	re = QueryInformationJobObject(hJob, JobObjectExtendedLimitInformation, &info, sizeof(info), NULL);



	return 0;
}