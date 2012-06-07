#include "Mutex.h"
#include "CriticalSection.h"

using namespace concurrent;

Mutex::Mutex() {
	//InitializeCriticalSection(&criticalSection);
	criticalSection = new CriticalSection();
}

Mutex::~Mutex() {
	//DeleteCriticalSection(&criticalSection);	
	delete criticalSection;
}

void Mutex::Acquire() {
    //EnterCriticalSection(&criticalSection);
	criticalSection->adquire();
}

void Mutex::Release() {
    //LeaveCriticalSection(&criticalSection);
	criticalSection->release();
}
