#include "Window.h"

using namespace view;

Window::Window(void)
{
	init();
}

Window::Window(Scene* scene)
{
	this->scene = scene;
	init();
	// setea el observador que va a manejar la pantalla y asociar vistas a cada entidad creada en el Scene
	this->scene->setObserver(screenManager);
}

void Window::init()
{
	surface = NULL;
	delayTime = 0;
	fps = 30;
	interval = 1 * 1000 / fps;
	lastBulletTime = 0;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_EnableKeyRepeat(60, SDL_DEFAULT_REPEAT_INTERVAL);
	surface = new SDLSurface(scene ? scene->getWidth(): 640, scene ? scene->getHeight(): 480, 32);
	screenManager = new ScreenManager(surface);
}

Window::~Window(void)
{
	delete screenManager;
	delete surface;
	SDL_Quit();
}

void Window::checkFramesPerSecond(void)
{
	if (delayTime > SDL_GetTicks())
	{
		SDL_Delay(delayTime - SDL_GetTicks());
	}
	delayTime = SDL_GetTicks() + interval;	
}

void Window::setScene(Scene* scene)
{
	this->scene = scene;
	this->scene->setObserver(screenManager);
}

void Window::show(void)
{
	assert(scene); // tiene que haber un scene definido, sino aborta
	scene->initialize();
	handleEvents();
}

void Window::handleEvents(void)
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

		// actualiza datos
		loop();

		// procesa pintado de pantalla
		render();
	}
}

void Window::loop()
{
	double time = SDL_GetTicks();
	scene->update(time/1000);
}

void Window::render()
{
	screenManager->render();
	// hace flush del buffer
	surface->paint();
}

void Window::handleEvent(SDL_Event event)
{
	Uint8* keystates = SDL_GetKeyState(NULL);
	switch (event.type)
	{
		case SDL_QUIT:
			quit = 1;
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				scene->stopAcceleration();					
				break;
			case SDLK_RIGHT:
				scene->stopRotation();					
				break;
			case SDLK_LEFT:
				scene->stopRotation();					
				break;
			}
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = 1;
				break;
			case SDLK_RIGHT:
				scene->rotateShipToRight();
				if (keystates[SDLK_UP])
					scene->accelerateShip();
				break;
			case SDLK_LEFT:
				scene->rotateShipToLeft();	
				if (keystates[SDLK_UP])
					scene->accelerateShip();
				break;
			case SDLK_UP:
				scene->accelerateShip();
				if (keystates[SDLK_LEFT])
					scene->rotateShipToLeft();
				else if (keystates[SDLK_RIGHT])
					scene->rotateShipToRight();
				break;
			case SDLK_SPACE:
				// solamente permitir un disparo cada BULLET_DELAY milisegundos (para evitar una rafaga)
				if (lastBulletTime == 0 || (SDL_GetTicks() - lastBulletTime) > BULLET_DELAY)				
				{
					scene->addBullet((int)SDL_GetTicks()/1000);
					lastBulletTime = SDL_GetTicks();
				}
			}
		break;
	}
}
