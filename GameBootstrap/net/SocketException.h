#ifndef _SOCKETEXCEPTION_H_
#define _SOCKETEXCEPTION_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <exception>
#include <sstream>
#include <string>

using namespace std;

namespace net
{
class SocketException: public exception
{   
public:
    SocketException(void)
    {
        _error.append("Exception");
    }
	SocketException(int);
    SocketException(string);
	SocketException(string, int);
    virtual ~SocketException();
	virtual string getMessage(void);
    const char* what() const throw()
    {
        return _error.c_str();
    }
    int getErrorCode(void);    
    void setErrorCode(int);
private:
	string getErrorMessage(int);
    string _error;
	string customMessage;
    int errorCode;
	static int NO_ERROR_CODE;
};
};

#endif
