#ifndef _CONCURRENTEXCEPTION_H_
#define _CONCURRENTEXCEPTION_H_

#include <Windows.h>
#include <string>
#include <sstream>

using namespace std;

namespace concurrent
{
class ConcurrentException
{
public:
	ConcurrentException(int);
	ConcurrentException(string);
	virtual ~ConcurrentException(void);
	string getMessage(void);
private:
	string getErrorMessage(int);
	string message;
	int errorCode;
};
};

#endif
