#include "SDLEvent.h"

using namespace sdl;
using namespace sdl::event;

SDLEvent::SDLEvent(void)
{
}

SDLEvent::SDLEvent(SDL_Event* event)
{
	this->event = event;
}

SDLEvent::~SDLEvent(void)
{
}

SDLEvent::SDLEventType SDLEvent::getType(void)
{
	SDLEvent::SDLEventType type = UNSUPPORTED_EVENT_TYPE;
	switch (event->type)
	{
		case SDL_KEYDOWN:
			type = KEYBOARD_EVENT_TYPE;
			break;
		case SDL_KEYUP:
			type = KEYBOARD_EVENT_TYPE;
			break;
		case SDL_MOUSEBUTTONDOWN:
			type = MOUSE_EVENT_TYPE;
			break;
		case SDL_MOUSEBUTTONUP:
			type = MOUSE_EVENT_TYPE;
			break;
	}
	return type;
}

SDLComponent* SDLEvent::getSource(void)
{
	return eventSource;
}

SDL_Event* SDLEvent::getEvent(void)
{
	return event;
}

void SDLEvent::setSource(SDLComponent* component)
{
	this->eventSource = component;
}
