#include "NumberValidator.h"

using namespace persistence;

NumberValidator::NumberValidator(string name) : AttributeValidator(name)
{
}

NumberValidator::NumberValidator(string name, string defaultValue) : AttributeValidator(name, defaultValue)
{
}

NumberValidator::~NumberValidator(void)
{
}

void NumberValidator::validate(Attribute* attribute)
{
	if (attribute->getValue().compare("") == 0)
	{
		string message("El valor para el atributo ");
		message.append(expectedAttributeName).append(" en la linea ").append(toString(attribute->getLocation()->getLineNumber()));
		message.append(" no fue especificado.");
		Logger::instance().log(message);

		setDefaultValue(attribute);
	}
	else if (!isNumber(attribute->getValue()))
	{
		string message("El valor para el atributo ");
		message.append(expectedAttributeName).append(" en la linea ").append(toString(attribute->getLocation()->getLineNumber()));
		message.append(" no es valido, se esperaba un numero entero.");
		Logger::instance().log(message);

		setDefaultValue(attribute);
	}
	_isValidated = true;
}

bool NumberValidator::isNumber(string str)
{
	string numbers("0123456789");
	size_t isNumberFound = 1;
	for (size_t i=0; i<str.length() && isNumberFound!=string::npos; i++)
	{
		isNumberFound = numbers.find(str.at(i));
	}

	bool isValid = false;
	if (isNumberFound!=string::npos)
	{
		isValid = true;
	}
	return isValid;
}
