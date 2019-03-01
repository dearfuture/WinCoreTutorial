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


  DWORD         LimitFlags;//��Ҫ����������ṹ���У��Ǹ����������ã�
	PerProcessUserTimeLimit ��
		ÿ�����̵��û�ʱ�����ƣ�ÿ���������ĵ��û�ģʽ�µ�CPUʱ�䣬��λ��100���롣����ʾʱ�䲻�Ǻ���׼����ʱ�䣬�����Զ��˳���
		LimitFlags= JOB_OBJECT_LIMIT_PROCESS_TIME;

	PerJobUserTimeLimit��
		��ҵ�����н���һ�����ĵ��û�ģʽ�µ�CPUʱ�䣬��λ��100���롣�����ʱ�䵽�ˣ���ô��ҵ�е����н��̾��˳���
		LimitFlags=JOB_OBJECT_LIMIT_JOB_TIME;

	MinimumWorkingSetSize:
		WorkingSetSize:
		PageFile:
		Windows�е��ڴ����:

	MaximumWorkingSetSize:

	ActiveProcessLimit:	��ҵ�����������ж��ٽ��̡��������������ƣ���ô�Ͳ��ܽ�����Ľ��̺������ҵ������ϵ�����Ҫ������ϵ����ô
						������̻��˳���

	Affinity: �������б�������ҵ�еĽ������Ǹ������������С�


	PriorityClass:

	SchedulingClass:
		