#include "AttributeValidator.h"

using namespace persistence;

AttributeValidator::AttributeValidator(string name)
{
	expectedAttributeName = name;
	defaultValue = "";
	isDefaultValue = false;
	_isValidated = false;
}

AttributeValidator::AttributeValidator(string name, string defaultValue)
{
	expectedAttributeName = name;
	this->defaultValue = defaultValue;
	isDefaultValue = true;
	_isValidated = false;
}

AttributeValidator::~AttributeValidator(void)
{
}

string AttributeValidator::getExpectedName(void)
{
	return expectedAttributeName;
}

bool AttributeValidator::isValidated(void)
{
	return _isValidated;
}

void AttributeValidator::setDefaultValue(Attribute* attribute)
{
	if (isDefaultValue)
	{
		attribute->setValue(defaultValue);

		string message("El valor del atributo ");
		message.append(expectedAttributeName).append(" fue modificado por el valor por defecto ").append(defaultValue).append(".");
		Logger::instance().log(message);
	}
}

void AttributeValidator::reset(void)
{
	_isValidated = false;
}

string AttributeValidator::toString(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}
