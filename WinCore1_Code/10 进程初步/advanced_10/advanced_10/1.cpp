#include<Windows.h>
#include<tchar.h>
#include<iostream>
using namespace std;
class A
{
public:
	A()
	{
		cout<<"this is C++ Global class"<<endl;
	}
	~A()
	{
		cout<<"this is C++ Global Detructor!"<<endl;
	}
};

A a;

int _tmain(int argc,TCHAR* argv[])
{

	_gettchar();
	return 0;
}