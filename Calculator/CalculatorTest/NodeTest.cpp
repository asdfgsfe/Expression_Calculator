#include <iostream>
#include "NodeTest.h"


NodeTest::NodeTest()
{
	std::cout << "NodeTest" << std::endl;
}

NodeTest::~NodeTest()
{
	std::cout << "~NodeTest" << std::endl;
}

void NodeTest::Calc() const
{
	std::cout << "NodeTest::Calc" << std::endl;
}