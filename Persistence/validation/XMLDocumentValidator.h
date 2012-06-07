#ifndef _XMLDOCUMENTVALIDATOR_H_
#define _XMLDOCUMENTVALIDATOR_H_

#include "..\persistence\Element.h"
#include "ElementValidator.h"
#include "AttributeValidator.h"
#include <map>
#include <list>
#include <string>
#include <sstream>

using namespace std;

namespace persistence
{
class XMLDocumentValidator
{
public:
	XMLDocumentValidator(void);
	virtual ~XMLDocumentValidator(void);
	
	void addElementValidator(ElementValidator*);
	void validate(Element*);
	list<Attribute*> getNonValidatedAttributes(Element*);
	void resetValidators(void);

private:
	ElementValidator* getElementValidator(string);
	string toString(int);
	map<string, ElementValidator*> validators;
};
};

#endif
