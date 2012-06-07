#include "Scene.h"
#include "EntityFactory.h"

using namespace model;

Scene::Scene(int width, int height)
{
	this->width  = width;
	this->height = height;
	observer     = NULL;
}

Scene::~Scene(void)
{
	// borra los elementos entity
	for_each(asteroids.begin(), asteroids.end(), Utils::delete_object());
	for_each(bullets.begin(), bullets.end(), Utils::delete_object());	
	for_each(bonus.begin(), bonus.end(), Utils::delete_object());

	// limpia collecciones
	asteroids.clear();
	bullets.clear();
	bonus.clear();
}

void Scene::setObserver(ISceneObserver* observer)
{
	this->observer = observer;
}

list<Ship*> Scene::getShips()
{ 
	list<Ship*> shipList;
	map<string, Ship*>::iterator itShip;
	for(itShip=ships.begin(); itShip!=ships.end(); itShip++)
	{
		Ship* ship = (*itShip).second;
		shipList.push_back(ship);
	}
	
	return shipList;
}

void Scene::addShip(string id, Ship* ship)
{
	ships.insert(pair<string, Ship*>(id, ship));
}

int Scene::getWidth()
{
	return width;
}

int Scene::getHeight()
{
	return height;
}

void Scene::setAsteroids(list<Asteroid*> asteroids)
{
	this->asteroids = asteroids;
}

void Scene::initialize()
{
	Logger::instance().log("Cargando asteroides");
	list<Asteroid*>::iterator it;
	int pos = 0;
	for (it=asteroids.begin();it!=asteroids.end();it++)
	{
		// si un asteroide no entra en la pantalla, se omite
		if ((*it)->getType()->getHeight() >= getHeight() || (*it)->getType()->getWidth() >= getWidth())
		{
			stringstream msg;
			msg << "No se cargó el asteroide '" << (*it)->getType()->getName() 
				<< "' porque no entra en la pantalla. \nAsteroide -> " << (*it)->getType()->getHeight() 
				<< " x " << (*it)->getType()->getWidth()
				<< ".\nPantalla  -> " << getWidth() << " x " << getHeight() << endl;
			Logger::instance().log(msg.str(), Logger::LINFO);
			continue;
		}

		// si no existe la imagen asginada, usa una default
		if (!Utils::fileExists((*it)->getImagePath()))
		{
			stringstream msg;
			msg << "No se encontro imagen de asteroide: '" << (*it)->getImagePath() << "'. Usando default" << endl;
			Logger::instance().log(msg.str(), Logger::LINFO);
			(*it)->setImagePath(DEFAULT_ASTEROID);
		}

		// informa al observador de una nueva entidad
		if (observer)
			observer->newEntity((*it), (*it)->getType()->getWidth(), (*it)->getType()->getHeight());
	}

	Logger::instance().log("Cargando nave");
	
	map<string, Ship*>::iterator itShip;
	for(itShip=ships.begin(); itShip!=ships.end(); itShip++)
	{
		Ship* ship = (*itShip).second;

		// si no existe la imagen asginada, usa una default
		if (!Utils::fileExists(ship->getImagePath()))
		{
			stringstream msg;
			msg << "No se encontro imagen de nave: '" << ship->getImagePath() << "'. Usando default" << endl;
			Logger::instance().log(msg.str(), Logger::LINFO);
		
			if (!Utils::fileExists(DEFAULT_SHIP))
			{
				stringstream msg;
				msg << "No se encontro imagen DEFAULT de nave: '" << DEFAULT_SHIP << "'. Abortando ejecucion." << endl;
				Logger::instance().log(msg.str(), Logger::LINFO);
				throw  "No se encontro imagen de nave DEFAULT.";			
			}
			else
				ship->setImagePath(DEFAULT_SHIP);
		}

		// informa al observador de una nueva entidad
		if (observer)
			observer->newEntity(ship);

		bool spaceFound = this->defineShipPosition(ship,pos);
		if (!spaceFound)
			throw "No se encontro lugar para la nave.";

		pos++;
	}

}

void Scene::accelerateShip(string shipId)
{
	ships[shipId]->acelerate();
}

void Scene::stopAcceleration(string shipId)
{
	ships[shipId]->stopAceleration();
}

void Scene::rotateShipToLeft(string shipId)
{
	ships[shipId]->rotateLeft();
}

void Scene::rotateShipToRight(string shipId)
{
	ships[shipId]->rotateRight();
}

void Scene::stopRotation(string shipId)
{
	ships[shipId]->stopRotation();
}

void Scene::addBullet(double startTime, std::string shipId)
{
	if (!Utils::fileExists(DEFAULT_BULLET))
	{
		stringstream msg;
		msg << "No se encontro imagen DEFAULT de bullet: '" << DEFAULT_BULLET << "'. Abortando ejecucion." << endl;
		Logger::instance().log(msg.str(), Logger::LINFO);
		throw  "No se encontro imagen de bullet DEFAULT.";			
	}

	Ship* userShip = ships[shipId];

	Bullet *newBullet = EntityFactory::instance().createBullet(generateId(), 
		                                                       DEFAULT_BULLET, 
															   Point(userShip->getX()+20, userShip->getY()+25),
															   userShip->getBulletTimeout(),
															   startTime);															   

	newBullet->setDirectionOfVelocity(userShip->getRotation());
	newBullet->setRotation(userShip->getRotation()); 
	bullets.push_back(newBullet);

	// informa al observador de una nueva entidad
	if (observer)
		observer->newEntity(newBullet);
}

void Scene::addBonus(double startTime, int x, int y)
{
	srand ((unsigned int)time(NULL)); // initialize random seed
	char code; 
	switch( rand() % 5 + 1 )
	{
	case 1:
		code = CODE_BONUS_A;
		break ;
	case 2:
		code = CODE_BONUS_B;
		break ;
	case 3:
		code = CODE_BONUS_C;
		break ;
	case 4:
		code = CODE_BONUS_D;
		break ;
	case 5:
		code = CODE_BONUS_E;
		break ;
	}

	// Con cierta probabilidad se agrega un bonus
	if ((rand() % 100) < BONUS_PROBABILITY)
	{
		if (!Utils::fileExists(DEFAULT_BONUS))
		{
			stringstream msg;
			msg << "No se encontro imagen DEFAULT de bonus: '" << DEFAULT_BONUS << "'. Abortando ejecucion." << endl;
			Logger::instance().log(msg.str(), Logger::LINFO);
			throw  "No se encontro imagen de bonus DEFAULT.";			
		}

		Bonus *newBonus = EntityFactory::instance().createBonus(generateId(), Point(x, y), code, startTime);
		bonus.push_back(newBonus);

		// informa al observador de una nueva entidad
		if (observer)
			observer->newEntity(newBonus);
	}
}

void Scene::update(double time)
{
	list<Asteroid*>::iterator it;
    for (it=asteroids.begin();it!=asteroids.end();it++)
    {
		Asteroid *a = (*it);
		a->updatePositions(time);
		checkBordersAndEntityPosition(a);
	}

	list<Bullet*>::iterator it2;
    for (it2=bullets.begin();it2!=bullets.end(); )
    {
		Bullet *b = (*it2);
		b->updatePositions(time);
		if ((time - b->getStartTime()) >= b->getDuration())
		{
			if (observer)
				observer->removedEntity(b);

			delete b; // borra el Entity
			it2 = bullets.erase(it2); // remueve de la lista
		}
		else
		{
			++it2;
			checkBordersAndEntityPosition(b);
		}
	}

	list<Bonus*>::iterator it3;
    for (it3=bonus.begin();it3!=bonus.end(); )
    {
		Bonus *b = (*it3);
		if ((time - b->getStartTime()) >= BONUS_DURATION)
		{
			if (observer)
				observer->removedEntity(b);

			delete b; // borra el Entity
			it3 = bonus.erase(it3); // remueve de la lista
		}
		else
		{
			++it3;
		}
	}

	map<string, Ship*>::iterator itShip;
	for(itShip=ships.begin(); itShip!=ships.end(); itShip++)
	{
		(*itShip).second->updatePositions(time);
		checkBordersAndEntityPosition((*itShip).second);
	}
}

void Scene::checkBordersAndEntityPosition(Entity* e)
{
	int entityWidth = 0, entityHeight = 0;

	if (observer)
	{
		entityWidth  = observer->getEntityWidth(e);
		entityHeight = observer->getEntityHeight(e);
	}

	// Validacion de los bordes
	// si la entidad entera sale por el margen derecho, vuelve a aparecer por el izq

	if (e->getX() > getWidth())
		e->setX(0 - entityWidth);
	// si la entidad entera sale por el margen izq, vuelve a aparecer por el derecho
	else if (e->getX() + entityWidth < 0)
		e->setX(getWidth());

	// si la entidad entera sale por el margen inferior, vuelve a aparecer por el superior
	if (e->getY() > getHeight())
		e->setY(0 - entityHeight);
	// si la entidad entera sale por el margen superior, vuelve a aparecer por el inferior
	else if (e->getY() + entityHeight < 0)
		e->setY(getHeight());		
}

bool Scene::defineShipPosition(Ship* ship, int pos)
{
	int x = 0;
	int y = 0;
	bool posOK = true;
	bool spaceFound = false;
	
	list<Asteroid*> asteroids = this->getAsteroids();
	list<Asteroid*>::iterator it;
	srand ((unsigned int)time(NULL) + pos ); // initialize random seed

	//ciclamos MAX_TRY_SHIP veces para encontrar un lugar (o hasta que efectivamente encontremos un lugar)
	for (int i=0;i<MAX_TRY_SHIP && !spaceFound;i++)
	{
		posOK = true;	
		//Obtenemos dos valores random de x e y
		x = rand() % this->getWidth()+1;
		y = rand() % this->getHeight()+1;

		if ((x < 40 || x > (this->width-40) ) || (y < 40 || y > (this->height - 40) ))
			continue;

		//ciclamos por cada asteroide
		for (it=asteroids.begin();it!=asteroids.end();it++)
		{
			//Calculamos el x,y del centro de cada asteroide
			double asteroidX = (*it)->getX() + ((*it)->getType()->getWidth()/2);
			double asteroidY = (*it)->getY() + ((*it)->getType()->getHeight()/2);

			//calculamos el "diametro" del asteroide es decir la diagonal (de punta a punta), distancia maxima.
			double mod= sqrt(pow((double)(*it)->getType()->getWidth(),2) + pow((double)(*it)->getType()->getHeight(),2));
			
			//calculamos la distancia que hay entre el asteroide y la posicion aleatoria sugerida para la nave
			double distancia = sqrt(pow(asteroidX-(x+20), 2) + pow(asteroidY-(y+20), 2));
			
			//mod/2 seria el radio del asteroide. le sumo 60 que es la diagonal de la nave.
			//Si la distancia entre ambos es menor a eso entonces la posicion sugerida no sirve.
			if (distancia <  ((mod/2) + 60))
			{
				posOK = false;						
				break;
			}
		}
		//Si al salir del ciclo posOK esta en true significa que encontramos un lugar
		if (posOK)
			spaceFound = true;	
		
		//Esto lo hice por si queremos hacer un barrido a mano despues del primer random, en lugar de seguir tirando randoms cada vez.
		//Por ahora lo dejo comentado porque con el random es un poco mas rapido.
		//else
		////Sino se barre la pantalla buscando otor lugar
		//{
		//	if (x < this->width && y < this->height)
		//	{
		//		x++;
		//	}
		//	else if (x < this->width && y >= this->height)
		//	{
		//		x++;
		//		y=0;
		//	}
		//	else if (x >= this->width && y >= this->height)
		//	{
		//		x=0;
		//		y=0;
		//	}
		//	else if (x >= this->width && y < this->height)
		//	{
		//		x=0;
		//		y++;
		//	}				
		//}
	}

	//Si se econtro un lugar seteamos la posicion de la nave y devolvemos 0, sino devolemos 1.	
	
	if (spaceFound)
	{				
		ship->setPosition(x,y);
		double rotation = rand() % 360;
		ship->setRotation(rotation);
		return true;
	}
	else
		return false;	
}

std::string Scene::toString()
{
	stringstream info;
	info << "Scene: \n   >width:  " << width << "\n   >height: " << height << "\n\n";

	list<Asteroid*>::iterator itAsteroids;
	list<Bullet*>::iterator itBullets;
	std::map<std::string, Ship*>::iterator itShips;

	int i = 0;
	for(itAsteroids=asteroids.begin(); itAsteroids!=asteroids.end(); itAsteroids++, i++)
	{		
		info << "   Asteroide " << i << "--> (" << (*itAsteroids)->getX() << ", " << (*itAsteroids)->getY() << ")\n";
	}
	i = 0;
	info << "\n";
	for(itBullets=bullets.begin(); itBullets!=bullets.end(); itBullets++, i++)
	{		
		info << "   Bullet " << i << "--> (" << (*itBullets)->getX() << ", " << (*itBullets)->getY() << ")\n";
		info << "      > velocity: " << (*itBullets)->getVelocity() << "\n";
		info << "      > direction: " << (*itBullets)->getDirectionOfVelocity() << "\n";
	}
	i = 0;
	info << "\n";
	for(itShips=ships.begin(); itShips!=ships.end(); itShips++, i++)
	{		
		info << "   Ship " << i << "--> (" << (*itShips).second->getX() << ", " << (*itShips).second->getY() << ")\n";
		info << "      > velocity: " << (*itShips).second->getVelocity() << "\n";
		info << "      > rotation velocity: " << (*itShips).second->getRotationVelocity() << "\n";
		info << "      > direction: " << (*itShips).second->getDirectionOfVelocity() << "\n";
		info << "      > aceleration: " << (*itShips).second->getPropulsion() << "\n";
	}

	return info.str();
}

void Scene::randomizeShipsPosition()
{
	Logger::instance().log("Definiendo posicion random de naves");
	
	map<string, Ship*>::iterator itShip;
	int pos = 1;
	for(itShip=ships.begin(); itShip!=ships.end(); itShip++)
	{
		Ship* ship = (*itShip).second;
		
		bool spaceFound = this->defineShipPosition(ship,pos);
		if (!spaceFound)
			throw "No se encontro lugar para la nave.";
		pos++;
	}
}

int Scene::generateId()
{
	return asteroids.size() + ships.size() + bullets.size() + bonus.size() + 1;
}