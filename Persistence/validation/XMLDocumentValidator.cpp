#include "XMLDocumentValidator.h"

using namespace persistence;

XMLDocumentValidator::XMLDocumentValidator(void)
{
}

XMLDocumentValidator::~XMLDocumentValidator(void)
{
	validators.clear();
}

void XMLDocumentValidator::addElementValidator(ElementValidator* validator)
{
	validators.insert(pair<string, ElementValidator*>(validator->getExpectedName(), validator));
}

void XMLDocumentValidator::validate(Element* element)
{
	ElementValidator* validator = getElementValidator(element->getName());
	if (validator == 0)
	{
		string message("El elemento ");
		message.append(element->getName()).append(" en la linea ").append(toString(element->getLocation()->getLineNumber()));
		message.append(" no es requerido por lo que se omite.");
		Logger::instance().log(message);
	}
	else
	{
		validator->resetValidators();
		list<Attribute*> attributes = element->getAttributes();
		list<Attribute*>::iterator it;
		for (it=attributes.begin();it!=attributes.end();it++)
		{
			validator->validate(*it);
		}
	}
}

list<Attribute*> XMLDocumentValidator::getNonValidatedAttributes(Element* element)
{
	list<Attribute*> nonValidatedAttributes;
	ElementValidator* validator = getElementValidator(element->getName());
	if (validator != 0)
	{
		nonValidatedAttributes = validator->getNonValidatedAttributes(element);
	}
	return nonValidatedAttributes;
}

ElementValidator* XMLDocumentValidator::getElementValidator(string elementName)
{
	ElementValidator* validator = 0;
	map<string, ElementValidator*>::iterator it = validators.find(elementName);
	if (it != validators.end())
	{
		validator = (*it).second;
	}
	return validator;
}

void XMLDocumentValidator::resetValidators(void)
{
	map<string, ElementValidator*>::iterator it;
	for (it=validators.begin(); it!=validators.end(); it++)
	{
		(*it).second->resetValidators();
	}
}

string XMLDocumentValidator::toString(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}
