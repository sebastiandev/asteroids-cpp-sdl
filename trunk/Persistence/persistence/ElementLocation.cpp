#include "ElementLocation.h"

using namespace persistence;

ElementLocation::ElementLocation(int line, int column) : xmlLineNumber(line), xmlColumnNumber(column)
{

}

ElementLocation::~ElementLocation(void)
{
}

int ElementLocation::getLineNumber(void)
{
	return xmlLineNumber;
}

int ElementLocation::getColumnNumber(void)
{
	return xmlColumnNumber;
}
