#include "EntityRepository.h"

using namespace persistence;

EntityRepository::EntityRepository(void)
{
	handler = new EntitySAX2Handler();
}

EntityRepository::~EntityRepository(void)
{
	delete handler;
}

Scene* EntityRepository::loadScene(string configPath)// throw (PersistenceException)
{
	loadAllEntities(configPath);
	list<Ship*> ships = handler->getShips();

	Scene* scene = handler->getScene();
	list<Ship*>::iterator it;
	int i=0;
	int id = ships.size();
	for (it=ships.begin(); it!=ships.end(); it++, i++)
	{
		(*it)->setX(320 + i*40);
		(*it)->setY(240);

		string clientId;
		stringstream ss;
		ss << id;
		ss >> clientId;
		id--;
		scene->addShip(clientId, *it);
	}

	scene->setAsteroids(handler->getAsteroids());
	return scene;
}

Scene* EntityRepository::loadSceneWithoutShip(string configPath)// throw (PersistenceException)
{
	loadAsteroids(configPath);

	Scene* scene = handler->getScene();
	scene->setAsteroids(handler->getAsteroids());
	return scene;
}
void EntityRepository::loadAsteroids(string configPath)// throw (PersistenceException)
{
	handler->setDocumentValidator(createDocumentValidator());
	handler->loadShip(false);
	loadFile(configPath);
}

void EntityRepository::loadAllEntities(string configPath)// throw (PersistenceException)
{
	handler->setDocumentValidator(createDocumentValidator());
	loadFile(configPath);
}

void EntityRepository::loadFile(string path)// throw (PersistenceException)
{
	try
    {
         XMLPlatformUtils::Initialize();
    }
	catch (const XMLException& xmle)
    {
		throw PersistenceException(XMLString::transcode(xmle.getMessage()));
	}

	SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
	parser->setFeature(XMLUni::fgSAX2CoreValidation, false);
	parser->setFeature(XMLUni::fgXercesContinueAfterFatalError, false);
	parser->setContentHandler((ContentHandler*)handler);

	EntitySAX2ErrorHandler* errorHandler = new EntitySAX2ErrorHandler(path.c_str());
	parser->setErrorHandler((ErrorHandler*)errorHandler);

	try
	{
		XMLPScanToken token;
		XMLCh* xmlFile = XMLString::transcode(path.c_str());
		//parser->parse(xmlFile);
		if (!parser->parseFirst(xmlFile, token))
		{
			string message("Imposible iniciar el procesamiento del archivo de configuracion del juego.");
		}
		else
		{
			bool tokenParseResult = true;
			while (tokenParseResult)
			{
				tokenParseResult = parser->parseNext(token);
			}
		}
    }
    catch (const XMLException& xmle)
	{
		throw PersistenceException(XMLString::transcode(xmle.getMessage()), (const char*)xmle.getSrcLine(), (int)xmle.getSrcLine());
	}
	catch (const SAXParseException& saxpe)
	{
		throw PersistenceException(XMLString::transcode(saxpe.getMessage()), "asteroids.xml", (int)saxpe.getLineNumber(), (int)saxpe.getColumnNumber());
	}
	catch (...)
	{
		throw PersistenceException("Unexpected exception");
	}

	delete parser;
	XMLPlatformUtils::Terminate();
}

XMLDocumentValidator* EntityRepository::createDocumentValidator(void)
{
	XMLDocumentValidator* documentValidator = new XMLDocumentValidator();
	XMLValidatorFactory* validatorFactory = new XMLValidatorFactory();
	documentValidator->addElementValidator(validatorFactory->createAsteroidsRootElementValidator());
	documentValidator->addElementValidator(validatorFactory->createAsteroidTypesElementValidator());
	documentValidator->addElementValidator(validatorFactory->createAsteroidTypeElementValidator());
	documentValidator->addElementValidator(validatorFactory->createAsteroidsElementValidator());
	documentValidator->addElementValidator(validatorFactory->createAsteroidElementValidator());
	documentValidator->addElementValidator(validatorFactory->createShipElementValidator());
	delete validatorFactory;
	return documentValidator;
}
