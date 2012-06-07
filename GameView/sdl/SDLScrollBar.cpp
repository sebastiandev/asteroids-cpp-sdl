#include "SDLScrollBar.h"

using namespace sdl;

SDLScrollBar::SDLScrollBar(SDLSurface* surface) : SDLComponent(surface)
{
	this->name = "scrollbar";
	this->type = SDLComponent::SCROLLBAR;
	unitIncrement = 0;
	maximumIncrement = 0;
	increment = 0;
}

SDLScrollBar::~SDLScrollBar(void)
{
}

void SDLScrollBar::setUnitIncrement(int increment)
{
	unitIncrement = increment;
}

void SDLScrollBar::setMaximumIncrement(int value)
{
	maximumIncrement = value;
}

int SDLScrollBar::getMaximumIncrement(void)
{
	return maximumIncrement;
}

int SDLScrollBar::getIncrement(void)
{
	return increment;
}

void SDLScrollBar::processEvent(SDLEvent* sdlEvent)
{
	if (sdlEvent->getType() == SDLEvent::MOUSE_EVENT_TYPE)
	{
		SDLMouseEvent* mouseEvent = static_cast<SDLMouseEvent*>(sdlEvent);
		if (mouseEvent->getState() == SDLMouseEvent::BUTTON_PRESSED)
		{
			int buttonWidth = width;
			int buttonHeight = width;
			if (mouseEvent->getX() >= x && mouseEvent->getX() <= x+buttonWidth &&
				mouseEvent->getY() >= y && mouseEvent->getY() <= y+buttonHeight)
			{
				scrollUp();
			}
			else if (mouseEvent->getX() >= x && mouseEvent->getX() <= x+buttonWidth &&
				mouseEvent->getY() >= y+height-buttonHeight && mouseEvent->getY() <= y+height)
			{
				scrollDown();
			}
		}
	}
	SDLComponent::processEvent(sdlEvent);
}

void SDLScrollBar::draw(void)
{
	// Dibujo boton superior
	int upButtonHeight = width;
	int upButtonWidth = width;
	boxRGBA(sdlSurface->getSurface(), x, y, x+upButtonWidth-1, y+upButtonHeight, 0, 0, 0, 255);
	boxRGBA(sdlSurface->getSurface(), x+1, y+1, x+upButtonWidth-2, y+upButtonHeight-1, 255, 255, 255, 255);

	short xs[3], ys[3];
	xs[0] = x+5; // punto inicial
	xs[1] = x+9; // segundo vertice
	xs[2] = x+upButtonWidth-6; //tercer vertice

	ys[0] = y+upButtonHeight-6; // primer vertice de y, inicio
	ys[1] = y+6; // segundo vertice, aumenta altura
	ys[2] = y+upButtonHeight-6; // tercer vertice

	filledPolygonRGBA(sdlSurface->getSurface(), xs, ys, 3, 0, 0, 0, 255);
	
	// Dibujo boton inferior
	int downButtonHeight = width;
	int downButtonWidth = width;
	int downButtonY = y+height-downButtonHeight;

	boxRGBA(sdlSurface->getSurface(), x, downButtonY, x+downButtonWidth-1, downButtonY+downButtonHeight, 0, 0, 0, 255);
	boxRGBA(sdlSurface->getSurface(), x+1, downButtonY+1, x+downButtonWidth-2, downButtonY+downButtonHeight-1, 255, 255, 255, 255);

	xs[0] = x+5; // punto inicial
	xs[1] = x+9; // segundo vertice
	xs[2] = x+downButtonWidth-6; // tercer vertice

	ys[0] = downButtonY+6; // primer vertice de y, inicio
	ys[1] = downButtonY+downButtonHeight-6; // segundo vertice, aumenta altura
	ys[2] = downButtonY+6; // tercer vertice

	filledPolygonRGBA(sdlSurface->getSurface(), xs, ys, 3, 0, 0, 0, 255);

	// Dibujo el largo principal
	boxRGBA(sdlSurface->getSurface(), x, y+upButtonHeight, x+upButtonWidth-1, downButtonY, 0, 0, 0, 255);
	boxRGBA(sdlSurface->getSurface(), x+1, y+upButtonHeight+1, x+upButtonWidth-2, downButtonY-1, 255, 255, 255, 255);
}

void SDLScrollBar::scrollUp(void)
{
	if (increment < unitIncrement)
	{
		increment = 0;
	}
	else
	{
		increment -= unitIncrement;
	}
}

void SDLScrollBar::scrollDown(void)
{
	if (increment+unitIncrement < maximumIncrement)
	{
		increment += unitIncrement;
	}
	else
	{
		increment = maximumIncrement;
	}
}
