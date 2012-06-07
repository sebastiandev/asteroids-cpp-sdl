#include "SDLMouseEvent.h"

using namespace sdl::event;

SDLMouseEvent::SDLMouseEvent(SDL_Event* event) : SDLEvent(event)
{
}

SDLMouseEvent::SDLMouseEvent(SDLEvent* sdlEvent)
{
	this->event = sdlEvent->getEvent();
}

SDLMouseEvent::~SDLMouseEvent(void)
{
}

SDLMouseEvent::SDLButtonState SDLMouseEvent::getState(void)
{
	SDLButtonState state = BUTTON_PRESSED;
	if (event->button.state == SDL_RELEASED)
	{
		state = BUTTON_RELEASED;
	}
	return state;
}

int SDLMouseEvent::getX(void)
{
	return event->button.x;
}

int SDLMouseEvent::getY(void)
{
	return event->button.y;
}
