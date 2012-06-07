#include "EntitySAX2ErrorHandler.h"

using namespace persistence;

EntitySAX2ErrorHandler::EntitySAX2ErrorHandler(string filename) : xmlFilename(filename)
{
}

EntitySAX2ErrorHandler::~EntitySAX2ErrorHandler(void)
{
}

void EntitySAX2ErrorHandler::warning(const SAXParseException& spe)
{
	string message("El analizador de xml arrojo una advertencia al procesar el archivo ");
	message.append(xmlFilename).append(" en la linea ");
	message.append(toString((int)spe.getLineNumber())).append(" y columna ").append(toString((int)spe.getColumnNumber())).append(". ");
	message.append("El mensaje devuelto por el analizador de xml es: ").append(XMLString::transcode(spe.getMessage()));
	Logger::instance().log(message);
}

void EntitySAX2ErrorHandler::error(const SAXParseException& spe)
{
	string message("El analizador de xml arrojo un error recuperable al procesar el archivo ");
	message.append(xmlFilename).append(" en la linea ");
	message.append(toString((int)spe.getLineNumber())).append(" y columna ").append(toString((int)spe.getColumnNumber())).append(". ");
	message.append("El mensaje devuelto por el analizador de xml es: ").append(XMLString::transcode(spe.getMessage()));
	Logger::instance().log(message);
}

void EntitySAX2ErrorHandler::fatalError(const SAXParseException& spe)
{
	string message("El analizador de xml arrojo un error no recuperable al procesar el archivo ");
	message.append(xmlFilename).append(" en la linea ");
	message.append(toString((int)spe.getLineNumber())).append(" y columna ").append(toString((int)spe.getColumnNumber())).append(". ");
	message.append("El mensaje devuelto por el analizador de xml es: ").append(XMLString::transcode(spe.getMessage()));
	Logger::instance().log(message);
}

void EntitySAX2ErrorHandler::resetErrors(void)
{
}

string EntitySAX2ErrorHandler::toString(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}