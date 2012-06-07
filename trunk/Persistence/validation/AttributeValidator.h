#ifndef _ATTRIBUTEVALIDATOR_H_
#define _ATTRIBUTEVALIDATOR_H_

#include "..\persistence\Attribute.h"
#include "Logger.h"
#include <string>
#include <sstream>

using namespace util;
using namespace std;

namespace persistence
{
class AttributeValidator
{
public:
	AttributeValidator(string);
	AttributeValidator(string, string);
	virtual ~AttributeValidator(void);
	string getExpectedName(void);
	virtual void validate(Attribute*)=0;
	bool isValidated(void);
	void reset(void);
protected:
	void setDefaultValue(Attribute*);
	string toString(int);
	string expectedAttributeName;
	string defaultValue;
	bool isDefaultValue;
	bool _isValidated;
};
};

#endif
