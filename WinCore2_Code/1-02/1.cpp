#include<Windows.h>
#include<tchar.h>



/*
1.	��ҵ���Կ���һ�����̳أ�Job
2.	һ������һ������һ����ҵ���Ͳ����ټ�������һ����ҵ��
3.	һ������һ������һ����ҵ���Ͳ������˳�����
4.	��ҵҲ��һ���ں˶���
5.  ���һ�����̼�����һ����ҵ����ô�������ʹ��CreateProcess�����������ӽ��̣��Զ����뵽�����̼������ҵ�С�
	���򣬵���CreateProcess������ʱ����Ҫ��CREATE_BREAKAWAY_FROM_JOB��ʶ��
*/




int _tmain()
{
	/*
	�ж�һ�������Ƿ��Ѿ�������һ����ҵ�ĺ����ǣ�IsProcessInJob;
	BOOL WINAPI IsProcessInJob(
  __in      HANDLE ProcessHandle,
  __in_opt  HANDLE JobHandle,
  __out     PBOOL Result
);
	
	ProcessHandle:	Ҫ�жϵĽ��̾����
	JobHandle��		���������Ƿ���뵽JobHandle�����ҵ�У�
	Result��			�жϽ����
	*/

	DWORD re;

	BOOL Result;

	HANDLE hJob1=CreateJobObject(NULL,L"ydm");

	_tprintf(L"hJob1 = %X GetLastError = %d\n",hJob1,GetLastError());

	HANDLE hJob2=CreateJobObject(NULL,L"ydm");

	_tprintf(L"hJob2 = %X GetLastError = %d\n",hJob2,GetLastError());

	
	JOBOBJECT_EXTENDED_LIMIT_INFORMATION  info={0};

	info.BasicLimitInformation.LimitFlags=JOB_OBJECT_LIMIT_BREAKAWAY_OK;

	re =SetInformationJobObject(hJob1,JobObjectExtendedLimitInformation,(PVOID)&info,sizeof(info));






	/*

	BOOL WINAPI IsProcessInJob(
  __in      HANDLE ProcessHandle,
  __in_opt  HANDLE JobHandle,
  __out     PBOOL Result
);


	ProcessHandle	��Ҫ���ȷ�ϵĽ��̾�� A��
	JobHandle		��ҵ��� B
	Result			������������1����ô˵������A�Ѿ���������ҲB���������Aû�б��ŵ���ҵB�С�

	Return			�ɹ�������1�����򷵻�1


*/

	

	
	
	

	re = IsProcessInJob(GetCurrentProcess(),NULL,&Result);

	_tprintf(L" re  =  %d  Result = %d\n",re,Result);

	
	
	
	
	/////////////////////////////////////////////////////////
	STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

   
   


	/*

	BOOL WINAPI AssignProcessToJobObject(
  __in  HANDLE hJob,
  __in  HANDLE hProcess
);

	hJob:		Ҫ������hProcess������Ǹ���ҵ�ľ��
	Process:	Ҫ���뵽��ҵ�еĽ��̾��
	return:		�ɹ�����1�����򷵻�0

*/

	re=AssignProcessToJobObject(hJob1,GetCurrentProcess());

	_tprintf(L" re  =  %d \n",re);

	re = IsProcessInJob(GetCurrentProcess(),NULL,&Result);

	_tprintf(L" re  =  %d  Result = %d\n",re,Result);
	




	 // Start the child process. 
    if( !CreateProcess(L"x32.exe",   // No module name (use command line)
        NULL,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        0,          // Set handle inheritance to FALSE
        CREATE_BREAKAWAY_FROM_JOB,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi )           // Pointer to PROCESS_INFORMATION structure
    ) 
    {
        _tprintf(L"CreateProcess failed (%d).\n", GetLastError() );
        return 0;
    }
	/////////////////////////////////////////

	re = IsProcessInJob(pi.hProcess,hJob1,&Result);

	_tprintf(L" re  =  %d  pi.hProcess Result = %d\n",re,Result);

	_gettchar();

	CloseHandle(hJob1);
	CloseHandle(hJob2);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return 0;


}