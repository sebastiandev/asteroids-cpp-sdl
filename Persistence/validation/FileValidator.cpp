#include "FileValidator.h"

using namespace persistence;

FileValidator::FileValidator(string name) : AttributeValidator(name)
{
}

FileValidator::FileValidator(string name, string defaultValue) : AttributeValidator(name, defaultValue)
{
}

FileValidator::~FileValidator(void)
{
}

void FileValidator::validate(Attribute* attribute)
{
	if (attribute->getValue().compare("") == 0)
	{
		string message("El valor para el atributo ");
		message.append(expectedAttributeName).append(" en la linea ").append(toString(attribute->getLocation()->getLineNumber()));
		message.append(" no fue especificado.");
		Logger::instance().log(message);

		setDefaultValue(attribute);
	}
	else if (!isFileExists(attribute->getValue()))
	{
		string message("El valor para el atributo ");
		message.append(expectedAttributeName).append(" en la linea ").append(toString(attribute->getLocation()->getLineNumber()));
		message.append(" no es valido.");
		Logger::instance().log(message);

		setDefaultValue(attribute);
	}
	_isValidated = true;
}

bool FileValidator::isFileExists(string filePath)
{
	return Utils::fileExists(filePath);
}
