#include<cmath>
#include <cassert>
#include<iostream>

#include "Node.h"
#include "Storage.h"
#include "DebugNew.h"

double NumberNode::Calc() const
{
	return number_;
}

BinaryNode::~BinaryNode()
{
	//delete left_;
	//delete right_;
}

UnaryNode::~UnaryNode()
{
	//delete child_;
}

//double AddNode::Calc() const
//{
//	return left_->Calc() + right_->Calc();
//}
//
//double SubNode::Calc() const
//{
//	return left_->Calc() - right_->Calc();
//}
//
//double MutiplyNode::Calc() const
//{
//	return left_->Calc() * right_->Calc();
//}
//
//double DivideNode::Calc() const
//{
//	double divisor = right_->Calc();
//	if(divisor != 0.0)
//		return left_->Calc() / right_->Calc();
//	else
//	{
//		std::cout << "Error: divisor by zero " << std::endl;
//		return HUGE_VAL;
//	}
//}

double FunctionNode::Calc() const
{
	return (*pFun_)(child_->Calc());
}

double UMinusNode::Calc() const
{
	return -child_->Calc();
}

MultipleNode::~MultipleNode()
{
	//std::vector<Node*>::const_iterator it;
	//for (it = childs_.begin(); it != childs_.end(); ++it)
	//{
	//	delete *it;
	//}
}

double SumNode::Calc() const
{
	double result = 0.0;
	std::vector<Node*>::const_iterator childIt = childs_.begin();
	std::vector <bool>::const_iterator positiveIt = positives_.begin();
	for (; childIt != childs_.end() && positiveIt != positives_.end(); ++childIt, ++positiveIt)
	{
		assert(positiveIt != positives_.end());
		double val = (*childIt)->Calc();
		if (*positiveIt)
			result += val;
		else
			result -= val;
	}
	assert(positiveIt == positives_.end());

	return result;
}

double ProductNode::Calc() const
{
	double result = 1.0;
	std::vector<Node*>::const_iterator childIt = childs_.begin();
	std::vector <bool>::const_iterator positiveIt = positives_.begin();
	for (; childIt != childs_.end() && positiveIt != positives_.end(); ++childIt, ++positiveIt)
	{
		assert(positiveIt != positives_.end());
		double val = (*childIt)->Calc();
		if (*positiveIt)
			result *= val;
		else if(val != 0.0)
			result /= val;
		else
		{
			std::cout << "Divison by zero" << std::endl;
			return HUGE_VAL;
		}
	}
	assert(positiveIt == positives_.end());

	return result;
}

double VariableNode::Calc() const
{
	double x = 0.0;
	if (storage_.IsInit(id_))
	{
		x = storage_.GetValue(id_);
	}
	else
	{
		std::cout << "Use of uninitialized variable." << std::endl;
	}
	return x;
}
void VariableNode::Assign(double val)
{
	storage_.SetValue(id_, val);
}

bool VariableNode::IsLvalue() const
{
	return true;
}

double AssignNode::Calc() const
{
	double x = 0.0;
	x = right_->Calc();
	left_->Assign(x);
	return x;
}