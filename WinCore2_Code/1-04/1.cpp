#include<Windows.h>
#include<tchar.h>

/*

typedef struct _JOBOBJECT_END_OF_JOB_TIME_INFORMATION {
DWORD EndOfJobTimeAction;
} JOBOBJECT_END_OF_JOB_TIME_INFORMATION, PJOBOBJECT_END_OF_JOB_TIME_INFORMATION;

JOB_OBJECT_TERMINATE_AT_END_OF_JOB:	������ֵ������EndOfJobTimeAction����ô��Job���û�ʱ��ľ���ʱ��Job
									�еĽ����Զ���ֹ��

JOB_OBJECT_POST_AT_END_OF_JOB��	������ֵ������EndOfJobTimeAction����ô��Job���û�ʱ��ľ���ʱ��Job�е���ҵ�п��ܻ�
								�������С�
									
								��������ҵû�к�С�˿�����ϵ�Ļ�����ô��ҵ�еĽ�����Ȼ��ֹ��

*/


/*
typedef struct _JOBOBJECT_SECURITY_LIMIT_INFORMATION {
DWORD             SecurityLimitFlags;//��ʾ�ṹ���У�����������Ա�����У��Ǹ���Ա���������á�
HANDLE            JobToken;
PTOKEN_GROUPS     SidsToDisable;
PTOKEN_PRIVILEGES PrivilegesToDelete;
PTOKEN_GROUPS     RestrictedSids;
} JOBOBJECT_SECURITY_LIMIT_INFORMATION, *PJOBOBJECT_SECURITY_LIMIT_INFORMATION;


SecurityLimitFlags: JOB_OBJECT_SECURITY_FILTER_TOKENS
					��ʾSidsToDisable��PrivilegesToDelete��RestrictedSids���������У�������һ������NULL
					
					JOB_OBJECT_SECURITY_NO_ADMIN
					��ҵ�еĽ��̣�����ʹ�ù���Ա����

					JOB_OBJECT_SECURITY_ONLY_TOKEN
					ǿ����ҵ�еĽ��̣�ʹ�ýṹ����JobToken�������������ơ�

					JOB_OBJECT_SECURITY_RESTRICTED_TOKEN
					��ҵ�еĽ���ʹ�õ����ƣ�������CreateRestrictedToken��������������Ͳ��У�

SID						���൱�����֤��						

token					���ƣ��������棬��������֤�ţ���ȻҲ�п������������֤�ţ����У����ܸ���Щ�¡���Ȩ��	

Privilege				��Ȩ��							

SecurityDescriptor		��ȫ��������	


*/
