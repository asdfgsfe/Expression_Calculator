#include <iostream>
#include <string>
#include "Calc.h"

void Calc::Serialize(Serializer& out) const
{
	symTbl_.Serialize(out);
	storage_.Serialize(out);
}

void Calc::DeSerialize(DeSerializer& in)
{
	symTbl_.DeSerialize(in);
	storage_.DeSerialize(in);
}

unsigned int Calc::FindSymbol(const std::string& str) const
{
	return symTbl_.Find(str);
}

unsigned int Calc::AddSymbol(const std::string& str)
{
	return symTbl_.Add(str);
}

void Calc::ListFun() const
{
	unsigned int i;
	for (i = 0; i < funTbl_.GetSize(); ++i)
	{
		std::cout << symTbl_.GetSymbolName(i) << std::endl;
	}
}

void Calc::ListVar() const
{
	unsigned int i;
	for (i = funTbl_.GetSize(); i < symTbl_.GetCurId(); ++i)
	{
		std::string name = symTbl_.GetSymbolName(i);
		double val;

		if (GetVariableValue(i, val))
			std::cout << name << " = " << val << std::endl;
		else
			std::cout << name << " = ? "<< std::endl;
	}
}

bool Calc::GetVariableValue(unsigned int id, double& val) const
{
	if (storage_.IsInit(id))
	{
		val = storage_.GetValue(id);
		return true;
	}
	return false;
}