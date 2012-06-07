#include "PersistenceException.h"

using namespace persistence;

PersistenceException::PersistenceException(string msg, string _file, int _line, int _col) : message(msg), file(_file), line(_line), column(_col)
{
}

PersistenceException::~PersistenceException(void)
{
}

string PersistenceException::getMessage(void) const
{
	return message;
}

string PersistenceException::getConfigFile(void) const
{
	return file;
}

int PersistenceException::getLineError(void) const
{
	return line;
}

int PersistenceException::getColumnError(void) const
{
	return column;
}
