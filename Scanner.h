#ifndef _SCANNER_H_
#define _SCANNER_H_

#include<string>

enum EToken
{
	TOKEN_COMMAND,
	TOKEN_END,
	TOKEN_ERROR,
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MUTIPLY,
	TOKEN_DIVIDE,
	TOKEN_LPARENTHESIS,
	TOKEN_RPARENTHESIS,
	TOKEN_IDETIFIER,
	TOKEN_ASSIGN
};

class Scanner
{
public:
	Scanner(std::istream& in);
	void Accept();
	void AcceptCommand();
	double Number() const;
	EToken Token() const;
	std::string GetSymbol() const;
	bool IsEmpty() const;
	bool IsDone() const;
	bool IsCommand() const;
private:
	void ReadChar();
	std::istream& in_;
	int look_;
	double number_;
	EToken token_;
	std::string symbol_;
	bool isEmpty_;
};

#endif //_SCANNER_H_