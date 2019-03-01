#include<Windows.h>
#include<tchar.h>

/*

typedef struct _JOBOBJECT_END_OF_JOB_TIME_INFORMATION {
DWORD EndOfJobTimeAction;
} JOBOBJECT_END_OF_JOB_TIME_INFORMATION, PJOBOBJECT_END_OF_JOB_TIME_INFORMATION;

JOB_OBJECT_TERMINATE_AT_END_OF_JOB:	如果这个值被赋予EndOfJobTimeAction，那么当Job的用户时间耗尽的时候，Job
									中的进程自动终止。

JOB_OBJECT_POST_AT_END_OF_JOB：	如果这个值被赋予EndOfJobTimeAction，那么当Job的用户时间耗尽的时候，Job中的作业有可能会
								继续运行。
									
								如果这个作业没有和小端口做联系的话，那么作业中的进程依然终止。

*/


/*
typedef struct _JOBOBJECT_SECURITY_LIMIT_INFORMATION {
DWORD             SecurityLimitFlags;//表示结构体中，其他几个成员变量中，那个成员变量起作用。
HANDLE            JobToken;
PTOKEN_GROUPS     SidsToDisable;
PTOKEN_PRIVILEGES PrivilegesToDelete;
PTOKEN_GROUPS     RestrictedSids;
} JOBOBJECT_SECURITY_LIMIT_INFORMATION, *PJOBOBJECT_SECURITY_LIMIT_INFORMATION;


SecurityLimitFlags: JOB_OBJECT_SECURITY_FILTER_TOKENS
					表示SidsToDisable、PrivilegesToDelete、RestrictedSids三个变量中，至少有一个不是NULL
					
					JOB_OBJECT_SECURITY_NO_ADMIN
					作业中的进程，不能使用管理员令牌

					JOB_OBJECT_SECURITY_ONLY_TOKEN
					强制作业中的进程，使用结构体中JobToken参数给定的令牌。

					JOB_OBJECT_SECURITY_RESTRICTED_TOKEN
					作业中的进程使用的令牌，必须有CreateRestrictedToken函数创建，否则就不行！

SID						就相当于身份证号						

token					令牌，令牌上面，有你的身份证号，当然也有可能有其他身份证号，还有，你能干那些事。特权。	

Privilege				特权。							

SecurityDescriptor		安全描述符？	


*/
