#ifndef _NODE_H_
#define _NODE_H_

#include <cassert>
#include <vector>
#include <memory>
#include "FunctionTable.h"
#include "ptr_vector.h"

class Storage;

class Noncopyable
{
protected:
	Noncopyable() {}
	~Noncopyable() {}
private:
	Noncopyable(Noncopyable&);
	const Noncopyable operator=(Noncopyable&);
};

//实现继承 node的类也相当于将拷贝构造函数和等号私有化了
//因为要构造派生类 先要构造基类 而基类已经私有化等号和拷贝构造函数 不能构造了
class Node : private Noncopyable
{
public:
	virtual double Calc() const = 0;
	virtual bool IsLvalue() const
	{
		return false;
	}

	virtual void Assign(double val)
	{
		assert(!"Assingn called incorrectlly.");
	}

	virtual ~Node() {};
};

class NumberNode : public Node
{
public:
	NumberNode(double number) : number_(number) {}
	double Calc() const;
private:
	const double number_;
};

class BinaryNode : public Node
{
public:
	BinaryNode(/*Node**/std::auto_ptr<Node>& left, 
		/*Node**/ std::auto_ptr<Node>& right)
		: left_(left), right_(right) {}
	~BinaryNode();
protected:
	/*Node* const left_;
	Node* const right_;*/
	std::auto_ptr<Node> left_;
	std::auto_ptr<Node> right_;
};

class UnaryNode : public Node
{
public:
	UnaryNode(std::auto_ptr<Node>& child) : child_(child) {}
	~UnaryNode();
protected:
	std::auto_ptr<Node> child_;
};

class FunctionNode : public UnaryNode
{
public:
	FunctionNode(std::auto_ptr<Node>& child, PtrFun pFun) :
		UnaryNode(child), pFun_(pFun) {}
	double Calc() const;
private:
	PtrFun pFun_;
};

//class AddNode : public BinaryNode
//{
//public:
//	AddNode(Node* left, Node* right) : BinaryNode(left, right) {}
//	double Calc() const;
//};
//
//class SubNode : public BinaryNode
//{
//public:
//	SubNode(Node* left, Node* right) : BinaryNode(left, right) {}
//	double Calc() const;
//};
//
//class MutiplyNode : public BinaryNode
//{
//public:
//	MutiplyNode(Node* left, Node* right) : BinaryNode(left, right) {}
//	double Calc() const;
//};
//
//class DivideNode : public BinaryNode
//{
//public:
//	DivideNode(Node* left, Node* right) : BinaryNode(left, right) {}
//	double Calc() const;
//};

class UMinusNode : public UnaryNode
{
public:
	UMinusNode(std::auto_ptr<Node>& child) : UnaryNode(child) {}
	double Calc() const;
};

class MultipleNode : public Node
{
public:
	MultipleNode(std::auto_ptr<Node>& node)
	{
		AppendChild(node, true);
	}

	void AppendChild(std::auto_ptr<Node>& node, bool positive)
	{
		childs_.push_back(node.release()); //opterator new
		//childs_.push_back(node);  //error ????
		positives_.push_back(positive);
	}

	~MultipleNode();
protected:
	//std::vector<Node*> childs_;
	ptr_vector<Node> childs_;
	std::vector<bool> positives_;
};

class SumNode : public MultipleNode
{
public:
	SumNode(std::auto_ptr<Node>& node) : MultipleNode(node) {}
	double Calc() const;

};

class ProductNode : public MultipleNode
{
public:
	ProductNode(std::auto_ptr<Node>& node) : MultipleNode(node) {}
	double Calc() const;

};

class VariableNode : public Node
{
public:
	VariableNode(unsigned int id, Storage& storage)
		: id_(id), storage_(storage) {}
	double Calc() const;
	void Assign(double val);
	bool IsLvalue() const;
private:
	const unsigned int id_;
	Storage& storage_;
};

class AssignNode : public BinaryNode
{
public:
	AssignNode(std::auto_ptr<Node>& left, std::auto_ptr<Node>& right)
		: BinaryNode(left, right) 
	{
		assert(left_->IsLvalue());
	}
	double Calc() const;
};

#endif //_NODE_H_