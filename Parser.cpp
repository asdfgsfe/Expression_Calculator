#include <cstring>
#include <cassert>
#include <iostream>
#include <sstream>

#include "Parser.h"
#include "Scanner.h"
#include "Node.h"
#include "Calc.h"
#include "Exception.h"
#include "DebugNew.h"

Parser::Parser(Scanner& scanner, Calc& calc) 
	: scanner_(scanner), calc_(calc), tree_(0), status_(STATUS_OK)
{
}

Parser::~Parser()
{
	//delete tree_;
}

STATUS Parser::Parse()
{
	tree_ = Expr();
	if (!scanner_.IsDone())
	{
		status_ = STATUS_ERROR;
	}
	return status_;
}

std::auto_ptr<Node> Parser::Expr()
{
	std::auto_ptr<Node> node = Term();
	EToken token = scanner_.Token();
	//if (token == TOKEN_PLUS)
	//{
	//	scanner_.Accept();
	//	Node* nodeRight = Expr();
	//	node = new AddNode(node, nodeRight);
	//}
	//else if (token == TOKEN_MINUS)
	//{
	//	scanner_.Accept();
	//	Node* nodeRight = Expr();
	//	node = new SubNode(node, nodeRight);
	//}

	//Expr: = Term { ('+' | '-') Term }
	if (token == TOKEN_PLUS || token == TOKEN_MINUS)
	{
		/*MultipleNode* multipleNode = new SumNode(node);*/
		std::auto_ptr<MultipleNode> multipleNode(new SumNode(node));
		do
		{
			scanner_.Accept();
			std::auto_ptr<Node> nextNode = Term();
			multipleNode->AppendChild(nextNode, (token==TOKEN_PLUS));
			token = scanner_.Token();
		} while (token == TOKEN_PLUS || token == TOKEN_MINUS);
		node = multipleNode;
	}
	//expr := term = expr
	else if (token == TOKEN_ASSIGN)
	{
		scanner_.Accept();
		std::auto_ptr<Node> nodeRight = Expr();
		if (node->IsLvalue())
		{
			node = std::auto_ptr<Node>(new AssignNode(node, nodeRight));
		}
		else
		{
			status_ = STATUS_ERROR;
			//std::cout << "The left-hand side of an assignment must be a variable." << std::endl;
			//todo 抛出异常
			throw SyntaxError("The left-hand side of an assignment must be a variable.");
		}
	}

	return node;
}
std::auto_ptr<Node> Parser::Term()
{
	std::auto_ptr<Node> node = Factor();
	EToken token = scanner_.Token();
	//if (token == TOKEN_MUTIPLY)
	//{
	//	scanner_.Accept();
	//	Node* nodeRight = Term();
	//	node = new MutiplyNode(node, nodeRight);
	//}
	//else if (token == TOKEN_DIVIDE)
	//{
	//	scanner_.Accept();
	//	Node* nodeRight = Term();
	//	node = new DivideNode(node, nodeRight);
	//}
	//Expr: = Factor { ('*' | '/') Factor }
	if (token == TOKEN_MUTIPLY || token == TOKEN_DIVIDE)
	{
		//MultipleNode* multipleNode = new ProductNode(node);
		std::auto_ptr<MultipleNode> multipleNode(new ProductNode(node));
		do
		{
			scanner_.Accept();
			std::auto_ptr<Node> nextNode = Factor();
			multipleNode->AppendChild(nextNode, (token == TOKEN_MUTIPLY));
			token = scanner_.Token();
		} while (token == TOKEN_MUTIPLY || token == TOKEN_DIVIDE);
		node = multipleNode;
	}
	return node;
}

std::auto_ptr<Node> Parser::Factor()
{
	std::auto_ptr<Node> node;
	EToken token = scanner_.Token();
	if (token == TOKEN_LPARENTHESIS)
	{
		scanner_.Accept();		//Accept() '('
		node = Expr();
		if (scanner_.Token() == TOKEN_RPARENTHESIS)
		{
			scanner_.Accept();	//Accept() ')'	
		}
		else
		{
			status_ = STATUS_ERROR;
			//todo: 抛出异常
			//std::cout << "Missing parentthesis" << std::endl;
			throw SyntaxError("Missing parentthesis.");
		}
	}
	else if (scanner_.Token() == TOKEN_NUMBER)
	{
		node = std::auto_ptr<Node>(new NumberNode(scanner_.Number()));
		scanner_.Accept();
	}
	else if (scanner_.Token() == TOKEN_IDETIFIER)
	{
		std::string symbol = scanner_.GetSymbol();
		unsigned int id = calc_.FindSymbol(symbol);
		scanner_.Accept();

		if (scanner_.Token() == TOKEN_LPARENTHESIS)
		{
			scanner_.Accept();  //Accept(); '('
			node = Expr();
			if (scanner_.Token() == TOKEN_RPARENTHESIS)
			{
				scanner_.Accept();	//Accept(); ')'
				if (id != SymbolTable::IDNOTFOUND && calc_.IsFunction(id))
				{
					node = std::auto_ptr<Node>(new FunctionNode(node, calc_.GetFunction(id)));
				}
				else
				{
					status_ = STATUS_ERROR;
					//std::cout << "Unkonwn function." << "\""<<symbol<<"\"" << std::endl;
					char buf[256] = {0};
					//sprintf_s(buf, "Unkonwn function \"%s\".", symbol.c_str());
					std::ostringstream oss;
					oss << "Unkonwn function \""<< symbol << "\".";
					throw SyntaxError(oss.str());
				}
			}
			else
			{
				status_ = STATUS_ERROR;
				//std::cout << "Missing parentthsis in a function call." << std::endl;
				throw SyntaxError("Missing parentthsis in a function call.");
			}
		}
		else
		{
			if (id == SymbolTable::IDNOTFOUND)
			{
				id = calc_.AddSymbol(symbol);
			}
			node = std::auto_ptr<Node>(new VariableNode(id, calc_.GetStorage()));
		}
	}
	else if (scanner_.Token() == TOKEN_MINUS)
	{
		scanner_.Accept();   //Accept() '-'
		node = std::auto_ptr<Node>(new UMinusNode(Factor()));
	}
	else
	{
		status_ = STATUS_ERROR;
		//todo: 抛出异常
		//std::cout << "Not a vaild expression" << std::endl;
		throw SyntaxError("Not a vaild expression.");
	}
	return node;
}

double Parser::Calculate() const
{
	assert(tree_.get() != 0);
	return tree_->Calc();
}