#ifndef MUTEX_H_
#define MUTEX_H_

#include <stdio.h>

namespace concurrent
{
class CriticalSection;

class Mutex	
{
public:
    Mutex ();
    ~Mutex ();
private:
    //CRITICAL_SECTION _critSection;
	CriticalSection *criticalSection;

    friend class Lock;
    void Acquire ();
    void Release ();
};
};
#endif /* MUTEX_H_ */
