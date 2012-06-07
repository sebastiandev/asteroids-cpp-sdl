#ifndef _SDLEVENT_H_
#define _SDLEVENT_H_

#include "SDL.h"

namespace sdl
{
class SDLComponent;
namespace event
{
class SDLEvent
{
public:
	SDLEvent(SDL_Event*);
	virtual ~SDLEvent(void);

	typedef enum SDLEventType
	{
		UNSUPPORTED_EVENT_TYPE,
		KEYBOARD_EVENT_TYPE,
		MOUSE_EVENT_TYPE
	};

	SDLEventType getType(void);
	SDLComponent* getSource(void);
	SDL_Event* getEvent(void);
	friend class SDLKeyboardEvent;
	friend class SDLMouseEvent;
	friend class SDLComponent;
protected:
	SDLEvent(void);
	void setSource(SDLComponent*);
	SDL_Event* event;
	SDLComponent* eventSource;
};
};
};

#endif
