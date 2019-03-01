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


  DWORD         LimitFlags;//需要表明，这个结构体中，那个参数被设置！
	PerProcessUserTimeLimit ：
		每个进程的用户时间限制，每个进程消耗的用户模式下的CPU时间，单位是100纳秒。和显示时间不是很贴准。到时间，进程自动退出。
		LimitFlags= JOB_OBJECT_LIMIT_PROCESS_TIME;

	PerJobUserTimeLimit：
		作业中所有进程一共消耗的用户模式下的CPU时间，单位是100纳秒。当这个时间到了，那么作业中的所有进程就退出。
		LimitFlags=JOB_OBJECT_LIMIT_JOB_TIME;

	MinimumWorkingSetSize:
		WorkingSetSize:
		PageFile:
		Windows中的内存管理:

	MaximumWorkingSetSize:

	ActiveProcessLimit:	作业中做多能运行多少进程。如果超过这个限制，那么就不能将另外的进程和这个作业进行联系，如果要建立联系，那么
						这个进程会退出。

	Affinity: 处理器列表。限制作业中的进程在那个处理器中运行。


	PriorityClass:

	SchedulingClass:
		