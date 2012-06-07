#include "ScreenManager.h"

ScreenManager::ScreenManager(SDLSurface* surface, std::string backgroundImage)
{
	intro = NULL;
	background = NULL;
	maxEntityWidth  = 0;
	maxEntityHeight = 0;
	firstRender = true;
	this->surface = surface;
	this->backgroundImage = backgroundImage;
}
ScreenManager::ScreenManager(SDLSurface* surface)
{
	intro = NULL;
	background = NULL;
	maxEntityWidth  = 0;
	maxEntityHeight = 0;
	firstRender = true;
	this->surface = surface;
	this->backgroundImage = string(DEFAULT_BACKGROUND);
}

ScreenManager::~ScreenManager(void)
{
	delete intro;
	delete background;
	// borra los elementos entityView
	for_each(entityviews.begin(), entityviews.end(), Utils::delete_object());
	// vacia las colecciones
	entityviews.clear();
	mapEntityview.clear();
}

void ScreenManager::newEntity(Entity* entity, int width, int height)
{
	EntityView* entityView = new EntityView(entity, this->surface, width, height);
	entityviews.push_back(entityView);	
	mapEntityview.insert(pair<int, EntityView*>(entity->getId(), entityView));
}

void ScreenManager::newEntity(Entity* entity)
{
	EntityView* entityView;
	
	Ship* ship = dynamic_cast<Ship*>(entity);
	if (ship)
	{
		if (!Utils::fileExists(ship->getAcceleratedImagePath()))
		{
			stringstream msg;
			msg << "No se encontro imagen de la Nave ON: '" << ship->getAcceleratedImagePath() << "'. utilizando nave comun." << endl;
			Logger::instance().log(msg.str(), Logger::LINFO);
			entityView = new ShipView(entity, this->surface, ship->getImagePath());
		}
		else
		{
			entityView = new ShipView(entity, this->surface, ship->getAcceleratedImagePath());
		}
	}
	else
	{
		entityView = new EntityView(entity, this->surface);
	}
	entityviews.push_back(entityView);
	mapEntityview.insert(pair<int, EntityView*>(entity->getId(), entityView));
}

void ScreenManager::removedEntity(Entity* e)
{
	// remueve la entidad de la lista
	list<EntityView*>::iterator it;
    for (it=entityviews.begin();it!=entityviews.end();it++)
    {
		if ((*it)->getEntity()->getId() == e->getId())
		{
			delete (*it); // borra el entityView
			entityviews.erase(it); // remueve de la lista
			break;
		}
	}
	// remueve del mapa
	mapEntityview.erase(e->getId());
}

int ScreenManager::getEntityWidth(Entity* e)
{
	
	map<int, EntityView*>::iterator it = mapEntityview.find(e->getId());
	if (it != mapEntityview.end())
	{
		return (int)it->second->getWidth();
	}

	return 0;
}

int ScreenManager::getEntityHeight(Entity* e)
{
	map<int, EntityView*>::iterator it = mapEntityview.find(e->getId());
	if (it != mapEntityview.end())
	{
		return (int)it->second->getHeight();
	}

	return 0;
}

void ScreenManager::renderFirstScreen()
{
	double xfactor = 0, yfactor = 0;
	/*
	intro = new SDLSurface();
	intro->loadFromImage(DEFAULT_INTRO);
	// escalar imagen de intro
	double xfactor = ((double)surface->getOriginalWidth() / (double)intro->getOriginalWidth());
	double yfactor = ((double)surface->getOriginalHeight() / (double)intro->getOriginalHeight());
	intro->scale(xfactor, yfactor);

	surface->draw(intro, 0, 0);
	surface->paint();

	//SDL_Delay(1000);

	delete intro; // libera el surface de intro
	intro = NULL;
	*/

	background = new SDLSurface();
	//background->loadFromImage(DEFAULT_BACKGROUND);
	background->loadFromImage(backgroundImage.c_str());	

	// escalar imagen de background
	xfactor = ((double)surface->getOriginalWidth() / (double)background->getOriginalWidth());
	yfactor = ((double)surface->getOriginalHeight() / (double)background->getOriginalHeight());
	background->scale(xfactor, yfactor);

	firstRender = false;
}

void ScreenManager::render()
{
	if (firstRender)
	{
		renderFirstScreen();
	}
	else
	{
		// pinta primero el fondo (refresca la pantalla)
		if (surface)
		{
			surface->draw(background, 0, 0);

			list<EntityView*>::iterator it;
			for (it=entityviews.begin();it!=entityviews.end();it++)
			{
				(*it)->paint();
			}
		}
	}
}