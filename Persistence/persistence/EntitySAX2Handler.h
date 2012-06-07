#ifndef _ENTITYSAX2HANDLER_H_
#define _ENTITYSAX2HANDLER_H_

#include "..\validation\XMLDocumentValidator.h"
#include "..\validation\ElementValidator.h"
#include "Element.h"
#include "Attribute.h"
#include "ElementLocation.h"
#include "PersistenceException.h"
#include "model\AsteroidType.h"
#include "model\Asteroid.h"
#include "model\Ship.h"
#include "model\Scene.h"
#include "Logger.h"
#include <iostream>
#include <list>
#include <sstream>
#include <xercesc\sax\Locator.hpp>
#include <xercesc\sax2\DefaultHandler.hpp>
#include <xercesc\sax2\Attributes.hpp>

using namespace model;
using namespace util;
using namespace std;
using namespace xercesc;

namespace persistence
{
class EntitySAX2Handler : public DefaultHandler
{
public:
	EntitySAX2Handler(void);
	virtual ~EntitySAX2Handler(void);

	void         setDocumentValidator(XMLDocumentValidator*);
	virtual void startElement        (const XMLCh* const uri, const XMLCh* const localname, const XMLCh* const qname, const Attributes& attrs);
	virtual void endElement          (const XMLCh* const uri, const XMLCh *const localname, const XMLCh *const qname);
	virtual void setDocumentLocator  (const Locator* const);
	
	list<AsteroidType*> getAsteroidTypes(void);
	list<Asteroid*>     getAsteroids    (void);
	list<Ship*>         getShips        (void);
	Scene*              getScene        (void);

	void loadShip(bool val) { hasToLoadShip = val;}

private:

	list<Attribute*> getAttributes  (const Attributes&, ElementLocation*);
	Attribute*       findAttribute  (const string, list<Attribute*>);
	bool             areEqualStrings(string, string);
	int              toInteger      (string);
	AsteroidType*    getAsteroidType(string);

	const Locator*        xmlLocator;
	XMLDocumentValidator* documentValidator;
	list<AsteroidType*>   asteroidTypes;
	list<Asteroid*>       asteroids;
	list<Ship*>           ships;
	Scene*                scene;
	bool                  hasToLoadShip;

	int entityCounter;
};
};

#endif
