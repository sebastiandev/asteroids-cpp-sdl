#include "ClientView.h"

using namespace view;
using namespace sdl;

ClientView::ClientView(int width, int height, GameClient* eventHandler, string backgroundImage)
{
	// Tiene que crear un shared_pointer y que no llame al delete del objeto
	// porque no es el dueño. Usa una funcion lambda que no hace nada
	//handler.reset(eventHandler, [](AsteroidsClient* ptr) { });
	surface = NULL;
	handler = eventHandler;
	init(width, height, backgroundImage);
}

ClientView::ClientView(SDLSurface* screen, int width, int height, GameClient* eventHandler, string backgroundImage)
{
	// Tiene que crear un shared_pointer y que no llame al delete del objeto
	// porque no es el dueño. Usa una funcion lambda que no hace nada
	//handler.reset(eventHandler, [](AsteroidsClient* ptr) { });
	handler = eventHandler;
	surface = screen;
	surface->resetVideoMode(width, height, 32);
	init(width, height, backgroundImage);
}

ClientView::~ClientView(void)
{
	delete screenManager;
}

void ClientView::show()
{
	handleEvents();	
}

void ClientView::init(int width, int height, string backgroundImage)
{
	delayTime       = 0;
	fps             = 30;
	interval        = 1 * 1000 / fps;
	lastBulletTime  = 0;

	if (!surface)
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_EnableKeyRepeat(60, SDL_DEFAULT_REPEAT_INTERVAL);
		surface = new SDLSurface(width, height, 32);
	}

	screenManager = new ScreenManager(surface, backgroundImage);
}

void ClientView::addEntity(model::Entity *entity)
{
	screenManager->newEntity(entity);
}

void ClientView::removeEntity(model::Entity *entity)
{
	screenManager->removedEntity(entity);
}

void ClientView::handleEvents()
{
	SDL_Event event;
	quit = 0;
	while (!quit)
	{
		// regula FPS
		checkFramesPerSecond();
		if (SDL_PollEvent(&event))
		{
			handleEvent(event);			
		}

		// procesa pintado de pantalla
		render();
	}
}

void ClientView::checkFramesPerSecond(void)
{
	if (delayTime > SDL_GetTicks())
	{
		SDL_Delay(delayTime - SDL_GetTicks());
	}
	delayTime = SDL_GetTicks() + interval;
}

void ClientView::render(void)
{
	screenManager->render();
	surface->paint();
}

void ClientView::handleEvent(SDL_Event e)
{
	Uint8* keystates = SDL_GetKeyState(NULL);
	switch (e.type)
	{
		case SDL_QUIT:
			quit = 1;
			handler->sendEvent(GameEvent::QUIT);//AsteroidsEvent(AsteroidsEvent::QUIT));
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_UP:
				handler->sendEvent(GameEvent::STOP_ACCELERATE);//AsteroidsEvent(AsteroidsEvent::STOP_ACCELERATE));
				break;
			case SDLK_RIGHT:
				handler->sendEvent(GameEvent::STOP_ROTATION);//AsteroidsEvent(AsteroidsEvent::STOP_ROTATION));
				break;
			case SDLK_LEFT:
				handler->sendEvent(GameEvent::STOP_ROTATION);//AsteroidsEvent(AsteroidsEvent::STOP_ROTATION));
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = 1;
				handler->sendEvent(GameEvent::QUIT);//AsteroidsEvent(AsteroidsEvent::QUIT));
				break;
			case SDLK_q:
				quit = 1;
				handler->sendEvent(GameEvent::QUIT);//AsteroidsEvent(AsteroidsEvent::QUIT));
				break;
			case SDLK_RIGHT:				
				if (keystates[SDLK_UP])
				{
					handler->sendEvent(GameEvent::ACCELERATE_RIGHT);//AsteroidsEvent(AsteroidsEvent::ACCELERATE_RIGHT));
				}
				else
				{
					handler->sendEvent(GameEvent::ROTATE_RIGHT);//AsteroidsEvent(AsteroidsEvent::ROTATE_RIGHT));
				}
				break;
			case SDLK_LEFT:
				if (keystates[SDLK_UP])
				{
					handler->sendEvent(GameEvent::ACCELERATE_LEFT);//AsteroidsEvent(AsteroidsEvent::ACCELERATE_LEFT));
				}
				else
				{
					handler->sendEvent(GameEvent::ROTATE_LEFT);//AsteroidsEvent(AsteroidsEvent::ROTATE_LEFT));
				}
				break;
			case SDLK_UP:
				if (keystates[SDLK_LEFT])
				{
					handler->sendEvent(GameEvent::ACCELERATE_LEFT);//AsteroidsEvent(AsteroidsEvent::ACCELERATE_LEFT));
				}
				else if (keystates[SDLK_RIGHT])
				{
					handler->sendEvent(GameEvent::ACCELERATE_RIGHT);//AsteroidsEvent(AsteroidsEvent::ACCELERATE_RIGHT));
				}
				else
				{
					handler->sendEvent(GameEvent::ACCELERATE);//AsteroidsEvent(AsteroidsEvent::ACCELERATE));
				}
				break;
			case SDLK_SPACE:
				// solamente permitir un disparo cada BULLET_DELAY milisegundos (para evitar una rafaga)
				if (lastBulletTime == 0 || (SDL_GetTicks() - lastBulletTime) > 500)				
				{
					handler->sendEvent(GameEvent::SHOOT);//AsteroidsEvent(AsteroidsEvent::SHOOT));
					lastBulletTime = SDL_GetTicks();
				}
			}
		break;
	}
}
