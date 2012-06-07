#include "Attribute.h"

using namespace persistence;

Attribute::Attribute(string name, string value)
{
	this->name = name;
	this->value = value;
}


Attribute::~Attribute(void)
{
}

string Attribute::getName(void) const
{
	return name;
}

void Attribute::setValue(string value)
{
	this->value = value;
}

string Attribute::getValue(void) const
{
	return value;
}

void Attribute::setLocation(ElementLocation* location)
{
	this->location = location;
}

ElementLocation* Attribute::getLocation(void)
{
	return location;
}
