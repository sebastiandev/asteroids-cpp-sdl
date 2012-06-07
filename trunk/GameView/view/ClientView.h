#ifndef _CLIENTVIEW_H_
#define _CLIENTVIEW_H_

#include "ScreenManager.h"
#include "EntityView.h"
#include "..\sdl\SDLSurface.h"
#include "model\Entity.h"
#include "model\GameClient.h"
#include <string>
#include <memory>
#include <iostream>

using namespace model;
using namespace sdl;
using namespace std;

class AsteroidsEvent;
class AsteroidsClient;

namespace view
{
class ClientView
{
public:
	ClientView(int width, int height, GameClient* eventHandler, string backgroundImage);
	ClientView(SDLSurface *screen, int width, int height, GameClient* eventHandler, string backgroundImage);
	virtual ~ClientView(void);
	void show(void);
	void addEntity(Entity* entity);
	void removeEntity(Entity* entity);
	void hide(void) { quit = 1;}
private:
	void init(int width, int height, string backgroundImage);
	void handleEvents(void);
	void checkFramesPerSecond(void);
	void render(void);
	void handleEvent(SDL_Event);
	GameClient* handler;
	ScreenManager* screenManager;
	SDLSurface* surface;
	
	Uint32 delayTime;
	Uint32 fps;
	Uint32 interval;
	Uint32 lastBulletTime;
	int quit;
};
};

#endif