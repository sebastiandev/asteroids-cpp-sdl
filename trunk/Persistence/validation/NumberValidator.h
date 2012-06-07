#ifndef _NUMBERVALIDATOR_H_
#define _NUMBERVALIDATOR_H_

#include "AttributeValidator.h"
#include "..\persistence\Attribute.h"
#include "Logger.h"
#include <string>

using namespace util;
using namespace std;

namespace persistence
{
class NumberValidator : public AttributeValidator
{
public:
	NumberValidator(string);
	NumberValidator(string, string);
	virtual ~NumberValidator(void);
	virtual void validate(Attribute*);
private:
	bool isNumber(string);
};
};

#endif
