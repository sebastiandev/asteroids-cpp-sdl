#include "EntitySAX2Handler.h"
#include "..\..\GameModel\model\EntityFactory.h"

using namespace persistence;
using namespace util;

EntitySAX2Handler::EntitySAX2Handler(void)
{
	documentValidator = 0;
	entityCounter = 1;
}

EntitySAX2Handler::~EntitySAX2Handler(void)
{	
	delete scene;
	ships.clear();
	asteroids.clear();
	asteroidTypes.clear();
}

void EntitySAX2Handler::setDocumentValidator(XMLDocumentValidator* validator)
{
	documentValidator = validator;
}

void EntitySAX2Handler::startElement(const XMLCh* const uri, const XMLCh* const localname,
		const XMLCh* const qname, const Attributes& attrs)
{
	string elementName(XMLString::transcode(localname));
	ElementLocation* location = new ElementLocation((int)xmlLocator->getLineNumber(), (int)xmlLocator->getColumnNumber());
	Element* element = new Element(elementName);
	element->setLocation(location);
	element->addAttributes(getAttributes(attrs, location));
	list<Attribute*> nonValidatedElementAttributes;

	if (documentValidator != 0)
	{
		documentValidator->validate(element);
		nonValidatedElementAttributes = documentValidator->getNonValidatedAttributes(element);
		if (nonValidatedElementAttributes.size() > 0)
		{
			element->addAttributes(nonValidatedElementAttributes);
		}
	}

	if (elementName.compare("asteroids")==0)
	{
		int width = toInteger(findAttribute("ancho", element->getAttributes())->getValue());
		int height = toInteger(findAttribute("alto", element->getAttributes())->getValue());
		string background = findAttribute("imagen", element->getAttributes())->getValue();
		this->scene = new Scene(width, height);
		scene->setBackground(background);
	}
	else if (elementName.compare("tipoAsteroide")==0)
	{
		AsteroidType* asteroidType = new AsteroidType(findAttribute("nombre", element->getAttributes())->getValue());
		asteroidType->setImagePath(findAttribute("imagen", element->getAttributes())->getValue());
		asteroidType->setWidth(toInteger(findAttribute("ancho", element->getAttributes())->getValue()));
		asteroidType->setHeight(toInteger(findAttribute("alto", element->getAttributes())->getValue()));
		asteroidType->setRotationAngle(toInteger(findAttribute("rotacion", element->getAttributes())->getValue()));
		
		//chequea q no exista el tipo de asteroide declarado
		list<AsteroidType*>::iterator it;
		bool exists = false;
		for (it=asteroidTypes.begin();it!=asteroidTypes.end();it++)
		{
			if ((*it)->getName().compare(asteroidType->getName())==0)
			{
				stringstream line;
				line << element->getLocation()->getLineNumber();
				string message("El tipo '");
				message.append(asteroidType->getName()).append("' definido en la linea: ").append(line.str());
				message.append(" ya existe, por lo tanto se omite.");
				Logger::instance().log(message);
				exists = true;
			}
		}
		if (!exists)
		{
			asteroidTypes.push_back(asteroidType);
		}
	}
	else if (elementName.compare("asteroide")==0)
	{
		AsteroidType* asteroidType = getAsteroidType(findAttribute("tipo", element->getAttributes())->getValue());
		if (asteroidType != 0)
		{
			int x = toInteger(findAttribute("x", element->getAttributes())->getValue());
			int y = toInteger(findAttribute("y", element->getAttributes())->getValue());
			int direction = toInteger(findAttribute("direccion", element->getAttributes())->getValue());
			int velocity = toInteger(findAttribute("velocidad", element->getAttributes())->getValue());

			Asteroid* asteroid = EntityFactory::instance().createAsteroid(entityCounter++, asteroidType, Point(x, y), direction, asteroidType->getRotationAngle(), velocity);
			asteroids.push_back(asteroid);
		}
	}
	else if (elementName.compare("nave")==0 && hasToLoadShip)
	{		
		string image = findAttribute("imagen", element->getAttributes())->getValue();
		int rotationVelocity = toInteger(findAttribute("velRotacion", element->getAttributes())->getValue());
		int maxVelocity = toInteger(findAttribute("velMaxima", element->getAttributes())->getValue());
		int propulsion = toInteger(findAttribute("propulsion", element->getAttributes())->getValue());
		int friction = toInteger(findAttribute("friccion", element->getAttributes())->getValue());
		int bulletTimeOut = toInteger(findAttribute("duracionBala", element->getAttributes())->getValue());

		Ship *ship = EntityFactory::instance().createShip(entityCounter++, image, Point(), rotationVelocity, maxVelocity, propulsion, friction, bulletTimeOut);
		ships.push_back(ship);
	}

	delete element;
}

void EntitySAX2Handler::endElement(const XMLCh* const uri, const XMLCh *const localname, const XMLCh *const qname)
{
}

void EntitySAX2Handler::setDocumentLocator(const Locator* const locator)
{
	xmlLocator = locator;
}

list<AsteroidType*> EntitySAX2Handler::getAsteroidTypes(void)
{
	return asteroidTypes;
}

list<Asteroid*> EntitySAX2Handler::getAsteroids(void)
{
	return asteroids;
}

list<Ship*> EntitySAX2Handler::getShips(void)
{
	return ships;
}

Scene* EntitySAX2Handler::getScene(void)
{
	return scene;
}

Attribute* EntitySAX2Handler::findAttribute(const string attributeNameToFind, list<Attribute*> attributes)
{
	Attribute* attribute;
	bool found = false;
	list<Attribute*>::iterator it;
	for (it=attributes.begin();it!=attributes.end() && !found;it++)
    {
		if (areEqualStrings((*it)->getName(), attributeNameToFind))
		{
			attribute = *it;
			found = true;
		}
	}
	return attribute;
}

list<Attribute*> EntitySAX2Handler::getAttributes(const Attributes& attrs, ElementLocation* location)
{
	list<Attribute*> attributes;
	Attribute* attribute;
	XMLSize_t length = attrs.getLength();
	for (unsigned int i=0; i<length; i++)
	{
		attribute = new Attribute(XMLString::transcode(attrs.getLocalName(i)), XMLString::transcode(attrs.getValue(i)));
		attribute->setLocation(location);
		attributes.push_back(attribute);
	}
	return attributes;
}

bool EntitySAX2Handler::areEqualStrings(string s1, string s2)
{
	bool result = false;
	if (s1.compare(s2)==0)
	{
		result = true;
	}
	return result;
}

int EntitySAX2Handler::toInteger(string str)
{
	int intValue = 0;
	stringstream ss(str);
	ss >> intValue;
	return intValue;
}

AsteroidType* EntitySAX2Handler::getAsteroidType(string typeName)
{
	bool found = false;
	AsteroidType* asteroidType = 0;
	list<AsteroidType*>::iterator it;
    for (it=asteroidTypes.begin();it!=asteroidTypes.end() && !found;it++)
    {
		if ((*it)->getName().compare(typeName)==0)
		{
			found = true;
			asteroidType = *it;
		}
    }
	return asteroidType;
}
