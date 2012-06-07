#ifndef _CRITICALSECTION_H_
#define _CRITICALSECTION_H_

#include <Windows.h>

namespace concurrent
{
/*
 * A critical section object provides synchronization similar to that provided by a mutex object,
 * except that a critical section can be used only by the threads of a single process.
 */
class CriticalSection
{
public:
	CriticalSection(void);
	virtual ~CriticalSection(void);
	void adquire(void);
	void release(void);
private:
	CRITICAL_SECTION criticalSection;
};
};

#endif
