#include<Windows.h>
#include<tchar.h>



/*
1.	作业可以看成一个进程池；Job
2.	一个进程一旦加入一个作业，就不能再加入另外一个作业。
3.	一个进程一旦加入一个作业，就不能再退出来。
4.	作业也是一个内核对象。
5.  如果一个进程加入了一个作业，那么这个进程使用CreateProcess创建的所有子进程，自动加入到父进程加入的作业中。
	否则，调用CreateProcess函数的时候，需要有CREATE_BREAKAWAY_FROM_JOB标识。
*/




int _tmain()
{
	/*
	判断一个进程是否已经加入了一个作业的函数是：IsProcessInJob;
	BOOL WINAPI IsProcessInJob(
  __in      HANDLE ProcessHandle,
  __in_opt  HANDLE JobHandle,
  __out     PBOOL Result
);
	
	ProcessHandle:	要判断的进程句柄；
	JobHandle：		看看进程是否加入到JobHandle这个作业中；
	Result：			判断结果。
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


	ProcessHandle	需要检查确认的进程句柄 A。
	JobHandle		作业句柄 B
	Result			检查结果，如果是1，那么说明进程A已经被放入做也B，否则进程A没有被放到作业B中。

	Return			成功，返回1，否则返回1


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

	hJob:		要将进程hProcess加入的那个作业的句柄
	Process:	要加入到作业中的进程句柄
	return:		成功返回1，否则返回0

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