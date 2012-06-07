#include "Runnable.h"

concurrent::Runnable::Runnable(void)
{
}

concurrent::Runnable::~Runnable(void)
{
}

DWORD WINAPI concurrent::Runnable::execute(void* args)
{
	Runnable* runnable = reinterpret_cast<Runnable*>(args);
	return runnable->run();
}
