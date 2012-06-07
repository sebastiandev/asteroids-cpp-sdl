#pragma once

#include "event\SDLMouseEvent.h"

using namespace sdl::event;

namespace sdl
{
class MouseListener
{
public:
	MouseListener(void);
	virtual ~MouseListener(void);
	virtual void processMouseButtonPressed(SDLMouseEvent*)=0;
	virtual void processMouseButtonReleased(SDLMouseEvent*)=0;
};
};
