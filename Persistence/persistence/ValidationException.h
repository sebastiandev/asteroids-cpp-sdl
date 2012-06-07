#ifndef _VALIDATIONEXCEPTION_H_
#define _VALIDATIONEXCEPTION_H_

#include <string>

using namespace std;

namespace persistence
{
class ValidationException
{
public:
	ValidationException(string);
	virtual ~ValidationException(void);
	string getMessage(void) const;
private:
	string message;
};
};

#endif
