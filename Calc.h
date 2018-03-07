#ifndef _CALC_H_
#define _CALC_H_

#include "SymbolTable.h"
#include "Storage.h"
#include "FunctionTable.h"
#include "Serial.h"

class Parser;

class Calc : public Serializable
{
	friend class Parser;
public:
	Calc() : storage_(symTbl_), funTbl_(symTbl_) {};
	void Serialize(Serializer& out) const;
	void DeSerialize(DeSerializer& in);
	void ListFun() const;
	void ListVar() const;
private:
	//SymbolTable symTbl_;Storage storage_;两个定义的顺序不能交换
	//必须先有symTbl才有storage
	SymbolTable symTbl_;		
	FunctionTable funTbl_;
	Storage storage_;

	bool GetVariableValue(unsigned int id, double& val) const;
	unsigned int AddSymbol(const std::string& str);
	unsigned int FindSymbol(const std::string& str) const;
	Storage& GetStorage()
	{
		return storage_;
	}
	bool IsFunction(unsigned int id) const
	{
		return id < funTbl_.Size();
	}
	PtrFun GetFunction(unsigned int id) const
	{
		return funTbl_.GetFunction(id);
	}
};

#endif //_CALC_H_