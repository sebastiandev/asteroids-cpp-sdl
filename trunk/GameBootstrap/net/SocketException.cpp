#include "SocketException.h"

using namespace net;

int SocketException::NO_ERROR_CODE = 0;

SocketException::SocketException(string message)
{
	errorCode = NO_ERROR_CODE;
	customMessage = message;

	_error.clear();
	_error.append("Exception::");
	_error.append(message);
}

SocketException::SocketException(int errorCode)
{
	this->errorCode = errorCode;
	customMessage = "";
}

SocketException::SocketException(string message, int errorCode)
{
	this->errorCode = errorCode;
	customMessage = message;
}

SocketException::~SocketException(void)
{
}

int SocketException::getErrorCode()
{
	return errorCode;
}    
void SocketException::setErrorCode(int code)
{
	errorCode = code;
}

string SocketException::getMessage(void)
{
	string errorMessage(customMessage);
	size_t index = errorMessage.find_last_of(".");
	if (index==string::npos)
	{
		errorMessage.append(". ");
	}
	if (errorCode > NO_ERROR_CODE)
	{
		errorMessage.append("El error devuelto por el socket es: ").append(getErrorMessage(this->errorCode));
		errorMessage.append(".");
	}
	return errorMessage;
}

string SocketException::getErrorMessage(int errorCode)
{
	string message = "";
	char* errString = NULL;
    int size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
		0, errorCode, 0, (LPTSTR)&errString, 10, NULL);
	
	if (errString != NULL)
	{
		message.append(errString);
		LocalFree(errString);
	}
	return message;
}
