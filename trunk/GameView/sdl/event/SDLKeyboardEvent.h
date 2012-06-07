#ifndef _SDLKEYBOARDEVENT_H_
#define _SDLKEYBOARDEVENT_H_

#include "SDLEvent.h"

namespace sdl
{
namespace event
{
class SDLKeyboardEvent : public SDLEvent
{
public:
	SDLKeyboardEvent(SDL_Event*);
	SDLKeyboardEvent(SDLEvent*);
	virtual ~SDLKeyboardEvent(void);

	typedef enum SDLKeyState
	{
		KEY_PRESSED,
		KEY_RELEASED
	};

	typedef enum SDLKeyCode
	{
		KEY,
		SPACE,
		BACKSPACE,
		SHIFT,
		UNDEFINED
	};

	SDLKeyState getState(void);
	char getKeyChar(void);
	SDLKeyCode getKeyCode(void);
	SDLKeyCode getModifierCode(void);
private:
	void initializeKeyChar(void);
	void initializeKeyCode(void);
	void initializeModifierCode(void);
	bool isKeyChar(void);
	char keyChar;
	SDLKeyCode keyCode;
	SDLKeyCode modifierCode;
};
};
};

#endif
