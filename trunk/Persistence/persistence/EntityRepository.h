#ifndef _ENTITYREPOSITORY_H_
#define _ENTITYREPOSITORY_H_

#include "PersistenceException.h"
#include "EntitySAX2Handler.h"
#include "EntitySAX2ErrorHandler.h"
#include "..\validation\XMLDocumentValidator.h"
#include "..\validation\XMLValidatorFactory.h"
#include "model\Scene.h"
#include <list>
#include <xercesc\util\PlatformUtils.hpp>
#include <xercesc\util\XMLString.hpp>
#include <xercesc\util\XMLException.hpp>
#include <xercesc\sax2\SAX2XMLReader.hpp>
#include <xercesc\sax2\XMLReaderFactory.hpp>

using namespace model;
using namespace std;
using namespace xercesc;

const string CONFIG_FILE_PATH = "../config/asteroids.xml";

namespace persistence
{
class EntityRepository
{
public:
	EntityRepository(void);
	virtual ~EntityRepository(void);
	Scene* loadScene(string configPath="../config/asteroids.xml");// throw (PersistenceException);
	Scene* loadSceneWithoutShip(string configPath="../config/asteroids.xml");// throw (PersistenceException);
private:
	void loadAsteroids(string configPath);// throw (PersistenceException);
	void loadAllEntities(string configPath);// throw (PersistenceException);
	void loadFile(string configPath);// throw (PersistenceException);
	XMLDocumentValidator* createDocumentValidator(void);
	EntitySAX2Handler* handler;
};
};

#endif
