#include "SDLToggleButton.h"

using namespace sdl;

SDLToggleButton::SDLToggleButton(int xpos, int ypos, int w, int h, string text, SDLSurface* surface) : SDLButton(xpos, ypos, w, h, text, surface)
{
	name = "togglebutton";
	type = SDLComponent::TOGGLEBUTTON;
}

SDLToggleButton::~SDLToggleButton(void)
{
}

void SDLToggleButton::processEvent(SDLEvent* sdlEvent)
{
	if (sdlEvent->getType() == SDLEvent::MOUSE_EVENT_TYPE)
	{
		SDLMouseEvent* mouseEvent = static_cast<SDLMouseEvent*>(sdlEvent);
		if (mouseEvent->getState() == SDLMouseEvent::BUTTON_PRESSED &&
			mouseEvent->getX() >= x && mouseEvent->getX() <= x+width &&
			mouseEvent->getY() >= y && mouseEvent->getY() <= y+height)
		{
			select();
		}
	}
	SDLButton::processEvent(sdlEvent);
}

void SDLToggleButton::drawBorder(void)
{
	if (isSelected())
	{
		roundedBoxRGBA(sdlSurface->getSurface(), x, y, x+width, y+height, 10, 255, 0, 0, 255);
	}
	else
	{
		SDLButton::drawBorder();
	}
}

void SDLToggleButton::drawBackground(void)
{
	if (isSelected())
	{
		roundedBoxRGBA(sdlSurface->getSurface(), x+2, y+2, x+width-2, y+height-2, 10, 200, 200, 200, 255);
	}
	else
	{
		SDLButton::drawBackground();
	}
}
