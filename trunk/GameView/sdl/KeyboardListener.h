#pragma once

#include "event\SDLKeyboardEvent.h"

using namespace sdl::event;

namespace sdl
{
class KeyboardListener
{
public:
	KeyboardListener(void);
	virtual ~KeyboardListener(void);
	virtual void processKeyboardEvent(SDLKeyboardEvent*)=0;
};
};
