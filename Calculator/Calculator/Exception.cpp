#include "Exception.h"

const char* Exception::what() const throw()
{
	return message_.c_str();
}

const char* Exception::StackTrace() const throw()
{
	return stackTrace_.c_str();
}

void Exception::FillStackTrace()
{
	//仅适用于linux进行栈回溯
	//const int len = 200;
	//void* buf[len];
	//int nptrs = ::backtrace(buf, len);
	//char** strings = ::backtrace_symbols(buf, nptrs);
	//if (strings)
	//{
	//	for (int i = 0; i < nptrs; ++i)
	//	{
	//		stackTrace_ = append(strings[i]);
	//		stackTrace_.push_back("\n");
	//	}
	//	free(strings);
	//}



}