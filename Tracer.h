#ifndef _TRACER_H_
#define _TRACER_H_

#include <map>

#ifndef NDEBUG

void* operator new(size_t size, const char* file, long line);
void operator delete(void* p, const char*, long);

void operator delete(void* p);

void* operator new[](size_t size, const char* file, long line);
void operator delete[](void* p, const char*, long);

void* operator new[](size_t size);
void operator delete[](void* p);

class Tracer
{
private:
	class Entry
	{
	public:
		Entry(const char* file = 0, long line = 0)
			:file_(file), line_(line) {}
		const char* File() const { return file_; }
		long Line() const { return line_; }
	private:
		const char* file_;
		long line_;
	};

	class Lock
	{
	public:
		Lock(Tracer& tracer) : tracer_(tracer)
		{
			tracer_.lock();
		}
		~Lock()
		{
			tracer_.unlock();
		}
	private:
		Tracer& tracer_;
	};

	friend class Lock;
public:
	Tracer();
	~Tracer();

	void Add(void* p, const char* file, long line);
	void Remove(void* p);
	void Dump();

	static bool ready_;
private:
	std::map<void*, Entry> mapEntry_;
	int lockCout_;
	void lock() { ++lockCout_; }
	void unlock() { --lockCout_; }
};

//Tracer NewTracer; 会产生多重定义错误
#endif //NDEBUG

#endif //_TRACER_H_

