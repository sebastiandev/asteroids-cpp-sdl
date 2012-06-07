#include "CriticalSection.h"

concurrent::CriticalSection::CriticalSection(void)
{
	if (!InitializeCriticalSectionAndSpinCount(&criticalSection, 0))
	{
		GetLastError();
	}
}

concurrent::CriticalSection::~CriticalSection(void)
{
	DeleteCriticalSection(&criticalSection);
}

void concurrent::CriticalSection::adquire(void)
{
	if (!TryEnterCriticalSection(&criticalSection))
	{
		//Log::getInstance()->error("Unable to enter critical section.");
	}
}

void concurrent::CriticalSection::release(void)
{
	LeaveCriticalSection(&criticalSection);
}
