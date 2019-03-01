#include<Windows.h>
#include<tchar.h>

int _tmain(int argc,TCHAR* argv[])
{
	
	///////////////////////////////////
	/*获得命令行参数的一种办法*/
	LPTSTR pCommandLine;//LPTSTR是一个字符串！！！
	for(int i=0;i<argc;i++)
	{
		_tprintf(L"%s\n",argv[i]);
	}


	_tprintf(L"-----------------------------\n");


	////////////////////////////////////////////////////////
	/*获得命令行参数的第二种办法*/
	pCommandLine=GetCommandLine();//通过这种方式获得的命令行字符串，程序名被引号引起啦了。
	_tprintf(L"%s\n",pCommandLine);


	/*
	第一种办法貌似复杂，其实简单，因为，他已经把每个命令行的参数作为一个字符串，给你分割好了，不要你在去分析

	第二种，打印的时候，只打印一个字符串就可以了，看似简单，其实复杂，因为你必须进行字符串分析，才能得到
	命令行的每一个参数！


	*/

	_gettchar();
	return 0;
}




