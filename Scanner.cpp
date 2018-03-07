#include <cctype>
#include <iostream>
#include <sstream>
#include "Scanner.h"

Scanner::Scanner(std::istream& in) : in_(in)
{
	Accept();
	isEmpty_ = (token_ == TOKEN_END);
}

bool Scanner::IsEmpty() const
{
	return isEmpty_;
}

bool Scanner::IsDone() const
{
	return token_ == TOKEN_END;
}	

bool Scanner::IsCommand() const
{
	return token_ == TOKEN_COMMAND;
}

double Scanner::Number() const
{
	return number_;
}

std::string Scanner::GetSymbol() const
{
	return symbol_;
}

EToken Scanner::Token() const
{
	return token_;
}

void Scanner::ReadChar()
{
	look_ = in_.get();
	while (look_ == ' ' || look_ == '\t')
		look_ = in_.get();
}

void Scanner::Accept()
{
	ReadChar();
	switch (look_)
	{
	case '!':
		token_ = TOKEN_COMMAND;
		break;
	case  '+':
		token_ = TOKEN_PLUS;
		break;
	case '-':
		token_ = TOKEN_MINUS;
		break;
	case '*':
		token_ = TOKEN_MUTIPLY;
		break;
	case '/':
		token_ = TOKEN_DIVIDE;
		break;
	case '=':
		token_ = TOKEN_ASSIGN;
		break;
	case '(':
		token_ = TOKEN_LPARENTHESIS;
		break;
	case ')':
		token_ = TOKEN_RPARENTHESIS;
		break;
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		token_ = TOKEN_NUMBER;
		in_.putback(look_);
		in_ >> number_;
		break;
	case '\0': case '\n': case '\r': case EOF:
		token_ = TOKEN_END;
		break;
	default:
		if (isalpha(look_) || look_ == '_')
		{
			token_ = TOKEN_IDETIFIER;
			symbol_.erase();
			do
			{
				symbol_ += look_;
				look_ = in_.get();
			} while (isalnum(look_) || look_ == '_');
			in_.putback(look_);
		}
		else
			token_ = TOKEN_ERROR;
		break;
	}
}

void Scanner::AcceptCommand()
{
	ReadChar();
	symbol_.erase();
	while (!isspace(look_))
	{
		symbol_ += look_;
		look_ = in_.get();
	}
}