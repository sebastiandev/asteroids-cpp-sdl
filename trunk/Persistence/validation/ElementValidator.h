#ifndef _ELEMENTVALIDATOR_H_
#define _ELEMENTVALIDATOR_H_

#include "..\persistence\Element.h"
#include "..\persistence\Attribute.h"
#include "AttributeValidator.h"
#include "Logger.h"
#include <string>
#include <map>
#include <list>
#include <sstream>

using namespace util;
using namespace std;

namespace persistence
{
class ElementValidator
{
public:
	ElementValidator(string);
	virtual ~ElementValidator(void);
	string getExpectedName(void);
	void addAttributeValidator(AttributeValidator*);
	void validate(Attribute*);
	list<Attribute*> getNonValidatedAttributes(Element*);
	void resetValidators(void);
private:
	string toString(int);
	string expectedElementName;
	map<string, AttributeValidator*> attributesValidators;
};
};

#endif
