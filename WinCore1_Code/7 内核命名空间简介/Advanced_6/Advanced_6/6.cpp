#include<Windows.h>
#include<tchar.h>

int _tmain()
{
	HANDLE hMutex=CreateMutex(NULL,FALSE,L"ydm\\ydm");//������һ�����ֽ�NULL�Ļ����ں˶���
	//�����ں˶��󣺾���û�����ֵ��ں˶��������ں˶��󣬲����ڽ��̼乲��
	//�����ں˶�������ڽ��̼乲��
	//GUID=:ȫ��Ψһ��ʶ��Global Unique identification

	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{
		//_tprintf(L"%s,\n",L"this is the next instance!");
		return 0;
	}

	DWORD sessionid=0;
	DWORD processid=0;
	processid=GetProcessId(GetCurrentProcess());//��ȡ��ǰ���̽���ID
	//GetCurrentProcess()��õ�ǰ���̾����
	
	if(ProcessIdToSessionId(processid,&sessionid))//��ȡ��ǰ�����������Ǹ�session����˵�Ự�У�
		_tprintf(L"%s,%d\n",L"this is the first instance! and session id is ",sessionid);
	
	_gettchar();
	return 0;
}