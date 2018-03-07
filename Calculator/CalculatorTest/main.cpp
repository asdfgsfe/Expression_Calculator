#include <iostream>
#include <memory>
#include <vector>
using namespace std;

#include "DebugNew.h"
#include "NodeTest.h"
#include "ptr_vector.h"

class Test
{
public:
	Test()
	{
		cout << "Test..." << endl;
	}
	Test(const Test& other)
	{
		cout << "Copy Test..." << endl;
	}
	~Test()
	{
		cout << "~Test..." << endl;
	}

};

int main(void)
{
	//std::vector<Test*> v;
	//Test* t1 = new Test;
	//Test* t2 = new Test;
	//Test* t3 = new Test;

	//v.push_back(t1);
	//v.push_back(t2);
	//v.push_back(t3);

	ptr_vector<Test> v;
	Test* t1 = new Test;
	Test* t2 = new Test;
	Test* t3 = new Test;

	v.push_back(t1);
	v.push_back(t2);
	v.push_back(t3);

	return 0;
}

//int main(void)
//{
//	//int* p = new int;
//	//delete p;
//
//	//int* p2 = new int[5];
//	//delete[] p2;
//
//	NodePtr np(new NodeTest);
//	np->Calc();
//
//	NodePtr np2(np);
//	/*np2 = np;*/ //调用拷贝构造函数
//
//	NodePtr np3;
//	np3 = np2;  //调用等号 由于np2对象已经有了
//
//	//error vector不能存放智能指针
//	//auto_ptr<NodeTest> node(new NodeTest);
//	//vector<auto_ptr<NodeTest> > v;
//	//v.push_back(node);
//
//	return 0;
//}