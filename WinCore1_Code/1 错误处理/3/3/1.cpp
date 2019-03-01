#include<iostream>
using namespace std;

#define max(a,b) (a>b?a:b)

int main()
{
	//C中的内存分配
	int *p=(int*)malloc(sizeof(int));
	*p=100;
	cin>>*p;
	cout<<"p="<<*p<<endl;//这个语句，输出的值是多少？
	cout<<(void*)p<<endl;

	/*
	sizeof(int)在程序运行前，其值已经确定！！！！
	*p是多少，必须要等到程序运行起来，并且，运行到cin>>*p;这个语句以后，我们才能知道
	*p的值是多少。


	sizeof(int)的值，叫做编译时能确定的值
	*p的值，我们就叫做程序运行时能确定的值。
	*/




	//C++中的内存分配
	int *p1=new int;
	*p1=200;
	cout<<(void*)p1<<endl;
	cout<<&p<<"\t"<<&p1<<endl;


	/*
	p和p1是两个指针变量，他们两个都放在栈内存里边，因为他两个是自动变量，放在{}里面。

	p和p1指向的内存，是堆内存，new和malloc函数的作用基本相同，但用法稍微简单一点！！！！

	malloc(100);我这就分配了100个字节的内存
	new char[100]; 这也分配了100个字节的内存！！！

	*/

	//现在我们想分配一个100个字符的数组；
	char *a=(char*)malloc(100*sizeof(char));
	char *a1=new char[100];

	//释放内存
	free(a);
	delete [] a1;

	cout<<max(1,2)<<endl;

	if(1>2)
		printf("haha\n");
	else
		printf("lala\n");

	cin.get();
	cin.get();
	free(p);
	delete p1;
	return 0;
}


/*
宏就是编译时，能够确定的东西！！！！
*/

/*
编译程序和解释程序的概念
例如C就是编译型程序，当程序完成编译以后，立即生成可执行代码（这个可执行代码是二进制的机器语言）。

true basic就是一种解释型语言，解释型的语言，必须有一个解释器，程序边解释，边执行。
.bat批处理脚本，也是一种解释性语言。

解释型语言的优势！！移植性高。

Java：既有编译阶段，也有解释阶段。

解释型比编译型，还有一个有点：解释型程序，可以边运行，边优化，此时，解释型程序，可优化的时间点
就比编译型程序多，可以对程序进行更多的优化。

*/