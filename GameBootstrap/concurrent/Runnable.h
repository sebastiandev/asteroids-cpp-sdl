#ifndef _RUNNABLE_H_
#define _RUNNABLE_H_

#include <Windows.h>

namespace concurrent
{
class Runnable
{
public:
	Runnable(void);
	virtual ~Runnable(void);
	static DWORD WINAPI execute(void*);
protected:
	virtual DWORD run(void)=0;
};
};

#endif
