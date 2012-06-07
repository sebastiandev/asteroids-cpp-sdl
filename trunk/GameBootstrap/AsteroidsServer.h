#ifndef _ASTEROIDSSERVER_H_
#define _ASTEROIDSSERVER_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "net\TCPSocket.h"
#include "net\SocketException.h"
#include "..\GameModel\model\Scene.h"
#include "..\GameModel\model\Ship.h"
#include "..\GameModel\model\Ship.h"
#include "..\GameView\view\ScreenManager.h"

#include "concurrent\Runnable.h"
#include "concurrent\Thread.h"
#include "concurrent\ConcurrentException.h"
#include "..\Persistence\persistence\EntityRepository.h"
#include "AsteroidsMsg.h"
#include "ClientHandler.h"
#include "AsteroidsEventList.h"
#include <string>
#include <list>
#include <map>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
using namespace concurrent;
using namespace model;

typedef string _shipKey;
typedef pair<string, string> _shipImageValue;

namespace persistence
{
	class EntityRepository;
}
class Bootstrap;

class AsteroidsServer : public Runnable
{
public:
	AsteroidsServer(void);
	AsteroidsServer(Bootstrap* controller, int port, int maxclients, string filesDir, string sceneFile);
	virtual ~AsteroidsServer(void);

	void   start(int port, int maxclients, string filesDir, string sceneFile);
	Scene* getScene();

protected:
	string loadScene();
	void   waitForClients();
	void   sendSceneToClients(string sceneBytes);
	void   startGame();
	bool   clientsReadyForUpdate();
	void   initScene(string filesDir, string tempXMLWithShips);
	void   sendStatus(string status);
	
	DWORD  run(void);

	// Las instancias de las que no somos dueños, van como punteros normales para no liberarlos
	Bootstrap  *controller;
	Scene      *scene;

	// Los objetos de los que si somos dueños, los manejamos como auto_ptr para liberarlos al destruir la clase
	auto_ptr<ScreenManager>                 screenManager;
	auto_ptr<persistence::EntityRepository> entityRepository;

	AsteroidsEventList eventQueue;
	net::TCPSocket     serverSocket;

	list<net::TCPSocket*>              clients;
	list<string>                       images;
	list<pair<ClientHandler*, string>> clientHandlers;
	list<Asteroid*>                    asteroids;
	map<_shipKey, _shipImageValue >    shipImages;

    int port, maxclients;
	string filesDir, sceneFile, clientIdQuitEvent; 
};

#endif
