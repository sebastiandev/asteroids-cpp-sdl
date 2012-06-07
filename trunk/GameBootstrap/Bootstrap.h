#ifndef _BOOTSTRAP_H_
#define _BOOTSTRAP_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "..\Persistence\persistence\EntityRepository.h"
#include "..\Persistence\persistence\PersistenceException.h"
#include "..\Persistence\persistence\SceneRepository.h"

#include "model\Scene.h"
#include "view\Window.h"
#include "view\StartWindow.h"
#include "net\TCPSocket.h"
#include "..\GameView\sdl\SDLSurface.h"
#include "..\GameView\view\StartWindow.h"
#include "..\GameView\view\ClientView.h"
#include "AsteroidsMenuListener.h"
#include "AsteroidsServer.h"
#include "AsteroidsClient.h"
#include "..\GameModel\model\Scene.h"
#include "..\GameModel\model\Asteroid.h"
#include "..\GameModel\model\Ship.h"
#include "..\GameModel\model\Bullet.h"
#include "concurrent\Thread.h"
#include "Utils.h"
#include "Logger.h"
#include <iostream>
#include <list>
#include "..\GameView\sdl\mixer\mixer.h"

//#include "net\UDPServerSocket.h"
//#include "net\UDPClientSocket.h"

using namespace model;
using namespace view;
using namespace persistence;
using namespace util;
using namespace std;

class Bootstrap
{
public:
	Bootstrap(void);
	virtual ~Bootstrap(void);
	void start(void);
	void launchServer(void);
	void launchClient(void);
	void updateServerStatus(string status);
	void updateClientStatus(string status);
	void setSelectedShip(string ship) { selectedShip = ship;}
	void startGame(string sceneFile);
	void updateEntities(list<EntityData> asteroidsData, list<EntityData> shipsData, map<int, EntityData> bulletsData, map<int, EntityData> bonusData);
	void quitGame(void);
	void gameFinished(void);
	void quit(void);
private:
	void showMenu(void);
	void showGame(void);
	void cleanPendingEntities(void);
	SDLSurface* mainSurface;
	auto_ptr<ClientView> clientView;
	list<Asteroid*> asteroids;
	list<Ship*> ships;
	map<int, Bullet*> bullets;
	map<int, Bonus*> bonuses;
	list<Entity*> pendingToDelete;
	StartWindow* window;
	auto_ptr<AsteroidsServer> server;
	auto_ptr<AsteroidsClient> client;
	string selectedShip;
	string gameSceneFile;
	bool showGameView;
	Mixer* sound;
};

#endif
