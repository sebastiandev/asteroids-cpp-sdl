#ifndef _SDLMOUSEEVENT_H_
#define _SDLMOUSEEVENT_H_

#include "SDLEvent.h"

namespace sdl
{
namespace event
{
class SDLMouseEvent : public SDLEvent
{
public:
	SDLMouseEvent(SDL_Event*);
	SDLMouseEvent(SDLEvent*);
	virtual ~SDLMouseEvent(void);

	typedef enum SDLButtonState
	{
		BUTTON_PRESSED,
		BUTTON_RELEASED
	};

	SDLButtonState getState(void);
	int getX(void);
	int getY(void);
};
};
};

#endif
