#include "ElementValidator.h"

using namespace persistence;

ElementValidator::ElementValidator(string elementName)
{
	expectedElementName = elementName;
}

ElementValidator::~ElementValidator(void)
{
	attributesValidators.clear();
}

string ElementValidator::getExpectedName(void)
{
	return expectedElementName;
}

void ElementValidator::addAttributeValidator(AttributeValidator* attributeValidator)
{
	attributesValidators.insert(pair<string, AttributeValidator*>(attributeValidator->getExpectedName(), attributeValidator));
}

void ElementValidator::validate(Attribute* attribute)
{
	map<string, AttributeValidator*>::iterator it = attributesValidators.find(attribute->getName());
	if (it == attributesValidators.end())
	{
		string message("El atributo ");
		message.append(attribute->getName()).append(" en la linea ").append(toString(attribute->getLocation()->getLineNumber()));
		message.append(", incluido en el elemento ").append(expectedElementName).append(", no es requerido por lo que se omite.");
		Logger::instance().log(message);
	}
	else
	{
		AttributeValidator* attributeValidator = (*it).second;
		attributeValidator->validate(attribute);
	}
}

list<Attribute*> ElementValidator::getNonValidatedAttributes(Element* element)
{
	Attribute* attribute;
	list<Attribute*> attributes;
	map<string, AttributeValidator*>::iterator it;
	for (it=attributesValidators.begin();it!=attributesValidators.end();it++)
    {
		AttributeValidator* attributeValidator = (*it).second;
		if (!attributeValidator->isValidated())
		{
			string message("El atributo ");
			message.append(attributeValidator->getExpectedName()).append(" no fue encontrado");
			message.append(" en la linea ").append(toString(element->getLocation()->getLineNumber()));
			message.append(", pero es requerido por el elemento ");
			message.append(expectedElementName).append(". Se agrega este atributo con un valor por defecto.");
			Logger::instance().log(message);

			attribute = new Attribute(attributeValidator->getExpectedName(), "");
			attribute->setLocation(element->getLocation());
			attributeValidator->validate(attribute);
			attributes.push_back(attribute);
		}
	}
	return attributes;
}

void ElementValidator::resetValidators(void)
{
	map<string, AttributeValidator*>::iterator it;
	for (it=attributesValidators.begin();it!=attributesValidators.end();it++)
    {
		(*it).second->reset();
	}
}

string ElementValidator::toString(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}
