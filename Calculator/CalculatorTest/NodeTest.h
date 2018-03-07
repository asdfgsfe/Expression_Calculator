#ifndef _NODE_TEST_H_
#define _NODE_TEST_H_

class NodeTest
{
public:
	NodeTest();
	~NodeTest();
	void Calc() const;
};

class NodePtr
{
public:
	NodePtr(NodeTest* pNode = 0) : ptr_(pNode) {}
	~NodePtr() { delete ptr_; }
	NodePtr(NodePtr& other) : ptr_(other.Release()) {}

	NodePtr& operator=(NodePtr& other)
	{
		Reset(other.Release());
		return *this;
	}

	NodeTest& operator*() { return *Get(); }
	NodeTest* operator->() { return Get(); }
	NodeTest* Get() { return ptr_; }

	NodeTest* Release()
	{
		NodeTest* tmp = ptr_;
		ptr_ = 0;
		return tmp;
	}

	void Reset(NodeTest* ptr = 0)
	{
		if (ptr_ != ptr)
			delete ptr_;
		ptr_ = ptr;
	}
private:
	NodeTest* ptr_;
};

#endif //_NODE_TEST_H_

