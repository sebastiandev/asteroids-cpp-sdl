#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "..\sdl\SDLSurface.h"
#include "EntityView.h"
#include "ScreenManager.h"
#include "model\Scene.h"
#include "model\Ship.h"
#include "model\Asteroid.h"
#include <assert.h>

namespace view
{
class Window
{
public:
	Window(void);
	Window(Scene*);
	virtual ~Window(void);
	void show(void);
	void setScene(Scene*);

private:
	void init();
	void handleEvents(void);
	void checkFramesPerSecond(void);
	void loop();
	void render(void);
	void handleEvent(SDL_Event);
	ScreenManager* screenManager;
	Scene* scene;
	SDLSurface* surface;
	Uint32 delayTime;
	Uint32 fps;
	Uint32 interval;
	Uint32 lastBulletTime;
	int quit;
};
};

#endif
