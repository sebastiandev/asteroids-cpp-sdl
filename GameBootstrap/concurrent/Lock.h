#ifndef LOCK_H_
#define LOCK_H_

#include "Mutex.h"

namespace concurrent
{
class Lock 
{
public:
    Lock(Mutex &mutex);
    ~Lock();
private:
    Mutex & _mutex;
};
};

#endif /* LOCK_H_ */
