#include "ConcurrentException.h"

concurrent::ConcurrentException::ConcurrentException(string message)
{
	this->message = message;
	errorCode = 0;
}

concurrent::ConcurrentException::ConcurrentException(int errorCode)
{
	this->errorCode = errorCode;
	message = "";
}

concurrent::ConcurrentException::~ConcurrentException(void)
{
}

string concurrent::ConcurrentException::getMessage(void)
{
	string msg;
	if (errorCode > 0)
	{
		msg = getErrorMessage(this->errorCode);
	}
	else
	{
		msg = message;
	}
	return msg;
}

string concurrent::ConcurrentException::getErrorMessage(int errorCode)
{
	LPSTR errString = NULL;
    int size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 
		0, errorCode, 0, (LPWSTR)&errString, 0, 0);
     
     stringstream ss;
     ss << errString;
     LocalFree(errString);
     return ss.str();
}
