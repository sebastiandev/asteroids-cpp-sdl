#include "NameValidator.h"

using namespace persistence;

NameValidator::NameValidator(string name) : AttributeValidator(name)
{
}

NameValidator::NameValidator(string name, string defaultValue) : AttributeValidator(name, defaultValue)
{
}

NameValidator::~NameValidator(void)
{
}

void NameValidator::validate(Attribute* attribute)
{
	if (attribute->getValue().compare("") == 0)
	{
		string message("El valor para el atributo ");
		message.append(expectedAttributeName).append(" en la linea ").append(toString(attribute->getLocation()->getLineNumber()));
		message.append(" no fue especificado.");
		Logger::instance().log(message);

		setDefaultValue(attribute);
	}
	_isValidated = true;
}
