#include "Bootstrap.h"

#include "io\Dir.h"

using namespace net;
using namespace concurrent;

Bootstrap::Bootstrap(void)
{
	showGameView = false;
	selectedShip = "nave1";//default

	AsteroidsMenuListener* listener = new AsteroidsMenuListener(this);	
	window = new StartWindow(listener);
	mainSurface = window->getSurface();
	sound = new Mixer();
}

Bootstrap::~Bootstrap(void)
{
	delete window;
}

void Bootstrap::start()
{	
	SceneRepository* sceneRepository = new SceneRepository(CONFIG_SERVER_DIRECTORY);
	window->addScenes(sceneRepository->getSceneNames());
	delete sceneRepository;
	showMenu();
}

void Bootstrap::showMenu()
{
	window->show();
	if (showGameView)
	{
		showGame();
		gameFinished();
	}
}

void Bootstrap::launchServer()
{	
	string portStr = window->getServerPort();
	int port = atoi(portStr.c_str());
	string sceneName = window->getSceneName();
	sceneName.append(".xml");
	cout << "selected scenario is: " << sceneName << endl;

	server.reset(new AsteroidsServer(this, port, 2, "..\\config\\server", sceneName));
	Thread t(server.get());
	t.start();
}

void Bootstrap::launchClient()
{
	string ip = window->getClientHost();
	string portStr = window->getClientPort();
	selectedShip = window->getSelectedShipName();

	int port = atoi(portStr.c_str());
	client.reset(new AsteroidsClient(this, ip, port, selectedShip));
	Runnable* c = (Runnable*) client.get();
	Thread tc(c);//lient.get());
	tc.start();
}

void Bootstrap::startGame(string sceneFile)
{
	window->close();
	gameSceneFile = sceneFile;
	showGameView = true;
	
}

void Bootstrap::showGame()
{
	try
	{
		EntityRepository repository;
		Scene *scene = repository.loadScene(gameSceneFile);
		GameClient* c = (GameClient*) client.get();
		clientView.reset(new ClientView(mainSurface, scene->getWidth(), scene->getHeight(), c, scene->getBackground())); 

		asteroids = scene->getAsteroids();
		ships = scene->getShips();

		list<Asteroid*>::iterator itAsteroids;
		list<Ship*>::iterator itShips;

		for (itAsteroids=asteroids.begin(); itAsteroids!=asteroids.end(); itAsteroids++)
			clientView->addEntity((*itAsteroids));

		for (itShips=ships.begin(); itShips!=ships.end(); itShips++)
			clientView->addEntity((*itShips));
		sound->playMusic("..\\sounds\\musica_de_fondo.mid");
		clientView->show();
		
	}
	catch (...)
	{
		gameFinished();
	}
}

void Bootstrap::cleanPendingEntities()
{
	// limpia las entidades que debian ser borradas
	for_each(pendingToDelete.begin(), pendingToDelete.end(), Utils::delete_object());
	pendingToDelete.clear();
}

void Bootstrap::updateEntities(list<EntityData> asteroidsData, list<EntityData> shipsData, map<int, EntityData> bulletsData, map<int, EntityData> bonusData)
{
	try
	{
		if (clientView.get())
		{
			list<Asteroid*>::iterator itA;
			list<Ship*>::iterator itS;
			map<int, Bullet*>::iterator itB;
			map<int, Bullet*>::iterator itX;

			cleanPendingEntities();

			// actualiza asteroides
			list<EntityData>::iterator it;
			for (it=asteroidsData.begin(); it!=asteroidsData.end(); it++)
			{
				for(itA=asteroids.begin(); itA!=asteroids.end(); itA++)		
				{
					EntityData &a = (*it);
					if (a.id == (*itA)->getId())
					{					
						(*itA)->setPosition(a.x, a.y);
						break;
					}
				}
			}

			// actualiza naves
			for (it=shipsData.begin(); it!=shipsData.end(); it++)
			{
				for(itS=ships.begin(); itS!=ships.end(); itS++)		
				{
					EntityData &s = (*it);
					if (s.id == (*itS)->getId())
					{
						(*itS)->setPosition(s.x, s.y);
						(*itS)->setRotation(s.rotation);
						if (s.acelerated)
							(*itS)->acelerate();
						else
							(*itS)->stopAceleration();					
						break;
					}
				}
			}

			// actualiza bullets
			// Si un bullet de la lista del cliente no esta en la del servidor, entonces desaparecio y se tiene q borrar
			map<int, Bullet*>::iterator itClient;
			for (itClient=bullets.begin(); itClient!=bullets.end(); )
			{
				if ( bulletsData.find(itClient->first) == bulletsData.end())
				{
					clientView->removeEntity(itClient->second);
					pendingToDelete.push_back(itClient->second);//lo agruego a la lista de pendientes para borrar que se limpia en la proxima actualizacion

					itClient = bullets.erase(itClient);
				}
				else
				{
					//actualiza la posicion
					EntityData &b = bulletsData[itClient->first];
					itClient->second->setPosition(b.x, b.y);
					itClient->second->setRotation(b.rotation);
					itClient++;
				}		
			}

			// Si un bullet de la lista del servidor no esta en la del cliente, entonces es nueva y se agrega
			map<int, EntityData>::iterator itServer;
			for (itServer=bulletsData.begin(); itServer!=bulletsData.end(); itServer++)
			{
				if ( bullets.find(itServer->first) == bullets.end())
				{
					sound->freeChannelOne();
					EntityData b = itServer->second;
					Bullet *bullet = new Bullet();
					bullet->setImagePath(string("tmp\\bullet1.png"));
					bullet->setId(b.id);
					bullet->setPosition(b.x, b.y);
					bullet->setRotation(b.rotation);
					bullets.insert(pair<int, Bullet*>(b.id, bullet));
					clientView->addEntity(bullet);
					//agregar bala
					//sound->playMusic("C:\\all_together_now.mid");
					sound->playEffect("BALA");

				}
			}
			

			// actualiza bonus
			// Si un bonus de la lista del cliente no esta en la del servidor, entonces desaparecio y se tiene q borrar
			map<int, Bonus*>::iterator itClientX;
			for (itClientX=bonuses.begin(); itClientX!=bonuses.end(); )
			{
				if ( bonusData.find(itClientX->first) == bonusData.end())
				{
					clientView->removeEntity(itClientX->second);
					pendingToDelete.push_back(itClientX->second);//lo agruego a la lista de pendientes para borrar que se limpia en la proxima actualizacion

					itClientX = bonuses.erase(itClientX);
				}
				else
				{
					//actualiza la posicion
					EntityData &x = bonusData[itClientX->first];
					itClientX->second->setPosition(x.x, x.y);					
					itClientX++;
				}		
			}

			// Si un bonus de la lista del servidor no esta en la del cliente, entonces es nuevo y se agrega
			map<int, EntityData>::iterator itServerX;
			for (itServerX=bonusData.begin(); itServerX!=bonusData.end(); itServerX++)
			{
				if ( bonuses.find(itServerX->first) == bonuses.end())
				{
					EntityData x = itServerX->second;
					Bonus *bonus = new Bonus();
					bonus->setImagePath(string(DEFAULT_BONUS));
					bonus->setId(x.id);
					bonus->setPosition(x.x, x.y);
					bonuses.insert(pair<int, Bonus*>(x.id, bonus));
					clientView->addEntity(bonus);
				}
			}
		}
	}
	catch (...)
	{
		gameFinished();
	}
}

void Bootstrap::updateServerStatus(string status)
{
	if (window->isVisible())
	{
		window->setStatus(status);
	}
}

void Bootstrap::updateClientStatus(string status)
{
	if (window->isVisible())
	{
		window->setStatus(status);
	}
}

void Bootstrap::gameFinished()
{
	// vuelve a mostrar menu
	if (clientView.get())
		clientView->hide();

	showGameView = false;
	sound->~Mixer();

	mainSurface->resetVideoMode(430, 550, 32);
	window->setStatus(" ");
	showMenu();
}

void Bootstrap::quitGame()
{
	cout << "Quit Game" << endl;
	showGameView = false;
	if (clientView.get() != NULL)
	{		
		clientView->hide();
	}
}

void Bootstrap::quit()
{
	cout << "Close program" << endl;
	window->close();
}

int main(int argc, char *argv[])
{
	Logger::instance().log("Iniciando Asteroids");
	Bootstrap boot;
	boot.start();
	return 0;
}
