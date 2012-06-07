#include "Element.h"
#include "..\..\Util\Utils.h"

using namespace util;
using namespace persistence;

Element::Element(string name)
{
	this->name = name;
}

Element::~Element(void)
{
	//delete location;

	// borra los atributos de la coleccion
	//for_each(attributes.begin(), attributes.end(), Utils::delete_object());
	attributes.clear();
}

string Element::getName(void)
{
	return name;
}

void Element::addAttributes(list<Attribute*> attributes)
{
	this->attributes.splice(this->attributes.end(), attributes);
}

list<Attribute*> Element::getAttributes(void)
{
	return attributes;
}

void Element::setLocation(ElementLocation* location)
{
	this->location = location;
}

ElementLocation* Element::getLocation(void)
{
	return location;
}
