#include "AsteroidsServer.h"

#include "io\File.h"
#include "..\Util\Logger.h"
#include "..\Util\FileUtil.h"
#include "io\Dir.h"
#include "Bootstrap.h"
#include "io\Dir.h"

#define NAVE1 "nave1"
#define NAVE2 "nave2"
#define NAVE3 "nave3"
#define NAVE4 "nave4"
#define NAVE5 "nave5"
#define TAG_NAVE1 "\n<nave imagen=\"tmp\\nave1.png\" velRotacion=\"3\" velMaxima=\"100\" propulsion=\"40\" friccion=\"5\" duracionBala=\"3\" />"
#define TAG_NAVE2 "\n<nave imagen=\"tmp\\nave2.png\" velRotacion=\"3\" velMaxima=\"85\" propulsion=\"35\" friccion=\"5\" duracionBala=\"6\" />"
#define TAG_NAVE3 "\n<nave imagen=\"tmp\\nave3.png\" velRotacion=\"3\" velMaxima=\"180\" propulsion=\"70\" friccion=\"5\" duracionBala=\"4\" />"
#define TAG_NAVE4 "\n<nave imagen=\"tmp\\nave4.png\" velRotacion=\"3\" velMaxima=\"90\" propulsion=\"50\" friccion=\"5\" duracionBala=\"5\" />"
#define TAG_NAVE5 "\n<nave imagen=\"tmp\\nave5.png\" velRotacion=\"3\" velMaxima=\"120\" propulsion=\"50\" friccion=\"5\" duracionBala=\"3\" />"

using namespace io;
using namespace net;
using namespace concurrent;
using namespace persistence;
using namespace model;
using namespace util;
using namespace std;

AsteroidsServer::AsteroidsServer(void)
{
	controller = NULL;
}

AsteroidsServer::AsteroidsServer(Bootstrap *controller, int port, int maxclients, string filesDir, string sceneFile)
{
	this->controller = controller;
	this->port = port;
	this->maxclients = maxclients;
	this->filesDir = filesDir;
	this->sceneFile = sceneFile;
}

AsteroidsServer::~AsteroidsServer(void)
{
	for_each(clients.begin(), clients.end(), Utils::delete_object());	
}

DWORD AsteroidsServer::run(void)
{
	start(port, maxclients, filesDir, sceneFile);
	return 0;
}

void AsteroidsServer::sendStatus(string status)
{
	if (controller)
	{
		controller->updateServerStatus(status);
	}
}

void AsteroidsServer::start(int port, int maxclients, string filesDir, string sceneFile)
{
	try
	{
		//Levanta el servidor
		serverSocket.doBind(port);
		serverSocket.doListen(maxclients);

		sendStatus("Esperando conexion de clientes...");	
		waitForClients();

		sendStatus("Cargando escenario...");
		string sceneBytes = loadScene();
		sendSceneToClients(sceneBytes);
		
		cout << this->scene->toString() << endl;

		sendStatus("Iniciando juego.");
		startGame();

		// closing clients
		list<pair<ClientHandler*, string> >::iterator itHandlers;
		for (itHandlers=clientHandlers.begin(); itHandlers!=clientHandlers.end(); itHandlers++)
		{
			ClientHandler* clientHandler = (*itHandlers).first;
			if (clientHandler->getClientId().compare(clientIdQuitEvent) != 0)
			{
				cout << "closing client handler: " << clientHandler->getClientId() << endl;
				clientHandler->sendQuit();
			}
			else
			{
				clientHandler->stop();
			}
		}
		clientHandlers.clear();
		serverSocket.doClose();
	}
	catch (...)
	{
		sendStatus("Unexpected error");
		return;
	}
}

string AsteroidsServer::loadScene()
{
	//Abre el XML y lo pasa a un string
	list<string> filter;
	list<string> files = Dir::getFiles(filesDir, filter);
	list<string>::iterator it;
	string sceneToSend;
	for (it=files.begin();it!=files.end(); it++)
	{
		cout << *it << endl;
		size_t lastDir = (*it).find_last_of("\\");
		string file = (*it).substr(lastDir+1);
		if (file == sceneFile)
		{
			sceneToSend = (*it);
		}
	}
	// carga el archivo xml en un buffer
	string sceneXmlBytes = FileUtil::fileToString(sceneToSend);
	int indexEnd = sceneXmlBytes.find("</asteroides>");
	sceneXmlBytes = sceneXmlBytes.substr(0,indexEnd+13);

	// add client ships
	list<pair<ClientHandler*, string> >::iterator itHandlers;
	for (itHandlers=clientHandlers.begin(); itHandlers!=clientHandlers.end(); itHandlers++)
	{
		//Define el tag XML en base a la nave seleccionada por el cliente
		string selectedShip =itHandlers->second;
		string tag;
		if (selectedShip == NAVE1)
		{
			tag = TAG_NAVE1;
		}
		else if (selectedShip == NAVE2)
		{
			tag = TAG_NAVE2;
		}
		else if (selectedShip==NAVE3)
		{
			tag = TAG_NAVE3;
		}
		else if (selectedShip==NAVE4)
		{
			tag = TAG_NAVE4;
		}
		else if (selectedShip==NAVE5)
		{
			tag = TAG_NAVE5;
		}
		else
		{
			tag = TAG_NAVE1;
		}
		//Lo agrega al final del XML
		sceneXmlBytes.append(tag);
	}

	//Agrega elcierre del XML
	sceneXmlBytes.append("\n</asteroids>");

	//Escribe el nuevo xml incluyendo las naves:
	string tempXMLWithShips = filesDir + "\\asteroids_withShips.xml";
	fstream tempXMLWithShipsFile(tempXMLWithShips, ios::out);
	tempXMLWithShipsFile.write(sceneXmlBytes.c_str(), sceneXmlBytes.length());
	tempXMLWithShipsFile.flush();
	tempXMLWithShipsFile.close();

	initScene(filesDir, tempXMLWithShips);

	//Reemplaza los paths que hacen referencia a config por tmp, para el xml a enviar al cliente
	string from = "..\\config\\server";
	size_t aux = sceneXmlBytes.find(from);
	while(aux != string::npos)
	{
		size_t start_pos = sceneXmlBytes.find(from);
		sceneXmlBytes.replace(start_pos, from.length(), "tmp");
		aux = sceneXmlBytes.find(from);
	}

	return sceneXmlBytes;
}

void AsteroidsServer::waitForClients()
{
	//Entra en loop infinito esperando clientes
	while (true)
	{
		if (maxclients > 0)
		{
			// el cliente tiene que mandar la nave elegida para que se arme el xml adecuado
			TCPSocket *cliente = serverSocket.doAccept();
			string selectedShip = cliente->doReceive(";");

			ClientHandler* handler = new ClientHandler(cliente, maxclients, &eventQueue);
			clientHandlers.push_back(pair<ClientHandler*, string>(handler, selectedShip));
			maxclients--;
			stringstream ss;
			ss << "Cliente conectado! Esperando por " << maxclients << " cliente(s).";
			sendStatus(ss.str());
		}
		else
		{
			serverSocket.doClose();
			break;
		}
	}
}

void AsteroidsServer::sendSceneToClients(string sceneBytes)
{
	list<pair<ClientHandler*, string> >::iterator itHandlers;
	for (itHandlers=clientHandlers.begin(); itHandlers!=clientHandlers.end(); itHandlers++)
	{
		// setea el archivo scene construido con las naves seleccionadas de cada cliente
		// y lanza el thread de cada cliente
		(*itHandlers).first->setSceneFile(sceneBytes);
		(*itHandlers).first->setImages(filesDir, images);
		Thread thread((*itHandlers).first);
		thread.start();
	}

	for (itHandlers=clientHandlers.begin(); itHandlers!=clientHandlers.end(); itHandlers++)
	{
		ClientHandler* clientHandler = (*itHandlers).first;
		
		// espera q terminen los clientes
		while (!clientHandler->isReady())
		{
		}
		clientHandler->setReadyToStart();
	}
	//Remove temporal XML created to load scene
	//Dir::removeFile(tempXMLWithShips);

	//Define posicion random para las naves
	scene->randomizeShipsPosition();
}

void AsteroidsServer::startGame()
{
	list<Bullet*> bullets;
	list<Ship*> ships = scene->getShips();
	list<Bonus*> bonuses;
	list<AsteroidsEvent> events;
	list<AsteroidsEvent>::iterator itEvent;
	list<Asteroid*>::iterator itA;
	list<Ship*>::iterator itS;
	list<Bullet*>::iterator itB;
	list<Bonus*>::iterator itX;

	list<pair<ClientHandler*, string> >::iterator itHandlers;

	clock_t startTime = clock();
	clock_t delayTime = 0;
	clock_t interval  = 30;

	string clientIdQuitEvent;
	bool quitGame = false;

	// Mensaje inicializado para enviar updates
	AsteroidsMsg updateMsg(AsteroidsMsg::UPDATE_MSG);
	AsteroidsMsg lastUpdateMsg = updateMsg;

	// loop de actualizacion del modelo
	while (!quitGame)
	{
		////// Manejo de clock para ajustar tiempos
		if (delayTime > clock())
		{
			// espera el tiempo definido segun interval
			while ((delayTime - clock()) > 0)
			{ 
				Sleep(interval);
			}
		}
		delayTime = clock() + interval;
		double currentTime = ((double)(clock() - startTime))/1000.00;

		events.clear();
		events = eventQueue.removeAll();
		// procesar los eventos de cada cliente
		for (itEvent=events.begin(); itEvent!=events.end(); itEvent++)
		{
			if (itEvent->getType() == AsteroidsEvent::SHOOT)
			{
				//cout << "client " << itEvent->getClientId() << " shooted new bullet" << endl;
				scene->addBullet(currentTime, itEvent->getClientIdStr());
			}
			else if (itEvent->getType() == AsteroidsEvent::ACCELERATE)
			{
				//cout << "client " << itEvent->getClientIdStr() << " accelerating" << endl;
				scene->accelerateShip(itEvent->getClientIdStr());
			}
			else if (itEvent->getType() == AsteroidsEvent::ACCELERATE_LEFT)
			{
				//cout << "client " << itEvent->getClientId() << " accelerating left" << endl;
				scene->accelerateShip(itEvent->getClientIdStr());
				scene->rotateShipToLeft(itEvent->getClientIdStr());
			}
			else if (itEvent->getType() == AsteroidsEvent::ACCELERATE_RIGHT)
			{
				//cout << "client " << itEvent->getClientId() << " accelerating right" << endl;
				scene->accelerateShip(itEvent->getClientIdStr());
				scene->rotateShipToRight(itEvent->getClientIdStr());
			}
			else if (itEvent->getType() == AsteroidsEvent::ROTATE_LEFT)
			{
				//cout << "client " << itEvent->getClientId() << " rotating left" << endl;
				scene->rotateShipToLeft(itEvent->getClientIdStr());
			}
			else if (itEvent->getType() == AsteroidsEvent::ROTATE_RIGHT)
			{
				//cout << "client " << itEvent->getClientId() << " rotating right" << endl;
				scene->rotateShipToRight(itEvent->getClientIdStr());
			}
			else if (itEvent->getType() == AsteroidsEvent::STOP_ACCELERATE)
			{
				//cout << "client " << itEvent->getClientId() << " stopped accelerating" << endl;
				scene->stopAcceleration(itEvent->getClientIdStr());
			}
			else if (itEvent->getType() == AsteroidsEvent::STOP_ROTATION)
			{
				//cout << "client " << itEvent->getClientId() << " stoped rotating" << endl;
				scene->stopRotation(itEvent->getClientIdStr());
			}
			else if (itEvent->getType() == AsteroidsEvent::QUIT)
			{
				stringstream ss;
				ss << "El cliente " << itEvent->getClientIdStr() << " se ha desconectado.";
				sendStatus(ss.str());
				clientIdQuitEvent = itEvent->getClientIdStr();
				quitGame = true;
				break;
			}
		}
		if (quitGame)
		{
			break;
		}

		//ESTO ES TEMPORAL!! Agrego un bonus a mano cada vez q desaparese el anterior.
		//Lo pongo en una posicion random por ahora.
		//Una vez que tengamos los choques, solo se crearina los bonus cuando se rompe un asterisco.
		//////////////////////////////////////////////////////////////////////////////
		bonuses = scene->getBonus();
		if (bonuses.size() <= 0)
		{
			srand ((unsigned int)time(NULL));
			//Agregado para probar, genero bounus:
			scene->addBonus(currentTime,rand() % 800 + 1,rand() % 600 + 1);
		}
		//////////////////////////////////////////////////////////////////////////////

		// actualizar las posiciones de las entidades
		scene->update(currentTime);	
		bullets = scene->getBullets();
		bonuses = scene->getBonus();
		

		// enviar las nuevas posiciones de cada entidad
		updateMsg.reset();

		for (itA=this->asteroids.begin(); itA!=asteroids.end(); itA++)
		{
			updateMsg.addAsteroidPosition((*itA)->getId(), (*itA)->getX(), (*itA)->getY());
		}
		for (itS=ships.begin(); itS!=ships.end(); itS++)
		{					
			Ship *s = (*itS);
			updateMsg.addShipPosition(s->getId(), s->getX(), s->getY(), s->getRotation(),s->isAcelerated());
		}
		for (itB=bullets.begin(); itB!=bullets.end(); itB++)
		{
			updateMsg.addBulletPosition((*itB)->getId(), (*itB)->getX(), (*itB)->getY(), (*itB)->getRotation());
		}
		for (itX=bonuses.begin(); itX!=bonuses.end(); itX++)
		{
			updateMsg.addBonusPosition((*itX)->getId(), (*itX)->getX(), (*itX)->getY());
		}
		bool clientsReady = clientsReadyForUpdate();
		for (itHandlers=clientHandlers.begin(); itHandlers!=clientHandlers.end(); itHandlers++)
		{
			ClientHandler* clientHandler = (*itHandlers).first;
			if (clientHandler->getStatus() == ClientHandler::DISCONNECTED)
			{
				cout << "Client " << clientHandler->getClientId() << " lost connection. Aborting game..." << endl;
				clientIdQuitEvent = clientHandler->getClientId();
				quitGame = true;
				break;
			}
			else if (clientsReady)
			{
				clientHandler->sendUpdate(updateMsg);
				lastUpdateMsg = updateMsg;
			}
			else
			{
				//por las dudas les vuelve a mandar el ultimo update, hasta que vuelvan a contestar OK
				clientHandler->sendUpdate(lastUpdateMsg);
			}
		}
	}// end while
}

bool AsteroidsServer::clientsReadyForUpdate()
{
	list<pair<ClientHandler*, string> >::iterator itHandlers;
	for (itHandlers=clientHandlers.begin(); itHandlers!=clientHandlers.end(); itHandlers++)
	{					
		ClientHandler* clientHandler = (*itHandlers).first;
		if (!clientHandler->isReadyForNextUpdate())
		{
			return false;
		}
	}
	//cout << "Clients are ready for next update!" << endl;
	return true;
}

void AsteroidsServer::initScene(string filesDir, string tempXMLWithShips)
{	
	//Carga la scene completa incluyendo las naves desde el archivo XML temporal:
	entityRepository.reset(new EntityRepository());
	this->scene = entityRepository->loadScene(tempXMLWithShips);
	
	// Crea el screen manager sin un surface principal
	// lo vamos a usar para registrar las imagenes de las entidades
	// y poder conocer el tamaño de las mismas y resolver colisiones
	screenManager.reset(new ScreenManager(NULL));
	this->scene->setObserver(screenManager.get());
	this->scene->initialize();

	//carga las imagenes de los asteroides
	this->asteroids = this->scene->getAsteroids();
	list<Asteroid*>::iterator itAsteroid;
	for (itAsteroid=asteroids.begin();itAsteroid!=asteroids.end();itAsteroid++)
	{
		int index = (*itAsteroid)->getImagePath().find_last_of("\\");
		int size = (*itAsteroid)->getImagePath().size();
		string imgName = (*itAsteroid)->getImagePath().substr(index,size-index);
		images.push_back(filesDir + imgName); 
		cout << "Loading asteroid image: " << filesDir << imgName << endl;
	}

	// carga la imagen de fondo del scene
	int index = scene->getBackground().find_last_of("\\");
	int size  = scene->getBackground().size();
	string imgName = scene->getBackground().substr(index,size-index);
	images.push_back(filesDir + imgName); 
	cout << "Loading background image: " << filesDir << imgName << endl;

	// carga la lista de imagenes necesarias (que no figuran en el xml)
	this->images.push_back(filesDir + string("\\background1.png"));
	this->images.push_back(filesDir + string("\\bullet1.png"));
	this->images.push_back(filesDir + string("\\introAsteroides.png"));

	// carga las imagenes de las naves
	this->shipImages.insert( pair<_shipKey, _shipImageValue>( NAVE1, _shipImageValue (filesDir + string("\\nave1.png"), filesDir + string("\\nave1_on.png")) ) );
	this->shipImages.insert( pair<_shipKey, _shipImageValue>( NAVE2, _shipImageValue (filesDir + string("\\nave2.png"), filesDir + string("\\nave2_on.png")) ) );
	this->shipImages.insert( pair<_shipKey, _shipImageValue>( NAVE3, _shipImageValue (filesDir + string("\\nave3.png"), filesDir + string("\\nave3_on.png")) ) );
	this->shipImages.insert( pair<_shipKey, _shipImageValue>( NAVE4, _shipImageValue (filesDir + string("\\nave4.png"), filesDir + string("\\nave4_on.png")) ) );
	this->shipImages.insert( pair<_shipKey, _shipImageValue>( NAVE5, _shipImageValue (filesDir + string("\\nave5.png"), filesDir + string("\\nave5_on.png")) ) );
	
	list<pair<ClientHandler*, string> >::iterator itShips;
	for (itShips=clientHandlers.begin(); itShips!=clientHandlers.end();itShips++)
	{		
		string shipType;
		map<_shipKey, _shipImageValue >::iterator it = shipImages.find((*itShips).second);
		if (it != shipImages.end())
		{
			shipType = (*it).first;
			// agrega las imagenes a la lista de imagenes a mandar al cliente
			this->images.push_back(it->second.first);
			this->images.push_back(it->second.second);
			cout << "Client Ship image: " << it->second.first << ", " << it->second.second << endl;
		}
	}
}

Scene* AsteroidsServer::getScene()
{
	return this->scene;
}