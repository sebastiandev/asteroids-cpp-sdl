#ifndef _NAMEVALIDATOR_H_
#define _NAMEVALIDATOR_H_

#include "AttributeValidator.h"

namespace persistence
{
class NameValidator : public AttributeValidator
{
public:
	NameValidator(string);
	NameValidator(string, string);
	virtual ~NameValidator(void);
	virtual void validate(Attribute*);
};
};

#endif