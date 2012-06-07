#ifndef _THREAD_H_
#define _THREAD_H_

#include "Runnable.h"
#include "ConcurrentException.h"
#include <string>
#include <iostream>

using namespace std;

namespace concurrent
{
class Thread : public Runnable
{
public:
	Thread(void);
	Thread(Runnable*);
	virtual ~Thread(void);
	void start(void); //throw (ConcurrentException);
	int join(void);
	int join(int);
	void stop(void);
	void setExitCode(int);
	int getExitCode(void);
	friend class ThreadPool;

protected:
	virtual DWORD run(void);

private:
	HANDLE handle;
	DWORD id;
	Runnable* runnable;
	int exitCode;
};
};

#endif
