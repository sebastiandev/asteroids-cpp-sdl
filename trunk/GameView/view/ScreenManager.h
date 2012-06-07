#ifndef _SCREENMANAGER_H_
#define _SCREENMANAGER_H_

#include "EntityView.h"
#include "..\sdl\SDLSurface.h"
#include "..\..\GameModel\model\Entity.h"
#include "..\..\GameModel\model\ISceneObserver.h"
#include <list>
#include <map>
#include "..\..\GameModel\model\Constants.h"
#include "..\..\Util\Logger.h"
#include "..\..\Util\Utils.h"
#include <sstream>
#include "..\..\GameModel\model\Ship.h"
#include "ShipView.h"
#include <algorithm>

using namespace view;
using namespace util;

namespace view
{
class ScreenManager : public ISceneObserver
{
public:
	ScreenManager(sdl::SDLSurface* surface, std::string backgroundImage);
	ScreenManager(sdl::SDLSurface* surface);
	~ScreenManager(void);

	void render();

	// Metodos de la interfaz ISceneObserver
	void newEntity      (model::Entity* entity, int width, int height);
	void newEntity      (model::Entity* entity);

	void removedEntity  (model::Entity* e);

	int  getEntityWidth (model::Entity* e);
	int  getEntityHeight(model::Entity* e);

private:	

	void renderFirstScreen();

	SDLSurface* surface;
	SDLSurface* intro;
	SDLSurface* background;

	std::string backgroundImage;

	list<EntityView*>     entityviews;
	map<int, EntityView*> mapEntityview;

	bool firstRender;
	int maxEntityWidth, maxEntityHeight;
};
};
#endif