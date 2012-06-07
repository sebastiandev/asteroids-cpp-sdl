#include "Lock.h"

using namespace concurrent;

Lock::Lock ( Mutex & mutex ): _mutex(mutex) {
    _mutex.Acquire();
}

Lock::~Lock () {
    _mutex.Release();
}
