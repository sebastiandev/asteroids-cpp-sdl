#include "Thread.h"

concurrent::Thread::Thread(void)
{
    handle = CreateThread(0, 0, &Runnable::execute, (void*)this, CREATE_SUSPENDED|THREAD_TERMINATE|THREAD_QUERY_INFORMATION, &id);
	exitCode = GetLastError();
}

concurrent::Thread::Thread(Runnable* runnable)
{
	this->runnable = runnable;
	handle = CreateThread(0, 0, &Runnable::execute, (void*)this->runnable, CREATE_SUSPENDED|THREAD_TERMINATE|THREAD_QUERY_INFORMATION, &id);
	exitCode = GetLastError();
}

concurrent::Thread::~Thread(void)
{
}

void concurrent::Thread::start(void) //throw (ConcurrentException)
{
	if (handle != NULL)
	{
		if (ResumeThread(handle) < 0)
		{
			throw ConcurrentException(GetLastError());
		}
	}
	else
	{
		throw ConcurrentException("Unable to start thread with invalid handle.");
	}
}

int concurrent::Thread::join(void)
{
	return WaitForSingleObject(handle, INFINITE);
}

int concurrent::Thread::join(int timeout)
{
	return WaitForSingleObject(handle, timeout);
}

void concurrent::Thread::stop(void)
{
	TerminateThread(handle, GetExitCodeThread(handle, (LPDWORD)&exitCode));
	CloseHandle(handle);
}

void concurrent::Thread::setExitCode(int exitCode)
{
	this->exitCode = exitCode;
}

int concurrent::Thread::getExitCode(void)
{
	return exitCode;
}

DWORD concurrent::Thread::run(void)
{
    return 0;
}

