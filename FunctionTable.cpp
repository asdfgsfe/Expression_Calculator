#include <cmath>
#include <cassert>
#include <iostream>

#include "FunctionTable.h"
#include "SymbolTable.h"
#include "DebugNew.h"

struct FunctionEntry
{
	PtrFun pFun_;
	char* functionName_;
};

FunctionEntry Entrys[] =
{
	log, "log",
	log10, "log10",
	exp,  "exp",
	sqrt, "sqrt",
	sin, "sin",
	cos, "cos",
	tan, "tan",
	sinh, "sinh",
	cosh, "cosh",
	tanh, "tanh",
	asin, "asin",
	acos, "acos",
	atan, "atan"
};

FunctionTable::FunctionTable(SymbolTable& tbl) :
	size_(sizeof(Entrys)/sizeof(Entrys[0]))
{
	Init(tbl);
}
void FunctionTable::Init(SymbolTable& tbl)
{
	std::cout << "function list:" << std::endl;
	pFuns_ = new PtrFun[size_];
	
	unsigned int i;
	for (i = 0; i < size_; ++i)
	{
		pFuns_[i] = Entrys[i].pFun_;
		unsigned int j = tbl.Add(Entrys[i].functionName_);
		assert(j == i);
		std::cout << Entrys[i].functionName_ << std::endl;
	}
}

FunctionTable::~FunctionTable()
{
	delete[] pFuns_;
}
