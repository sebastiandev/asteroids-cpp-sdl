#include "SDLComponent.h"

using namespace sdl;

SDLComponent::SDLComponent(SDLSurface* surface) : sdlSurface(surface), x(0), y(0), width(0), height(0)
{
	viewport = new Viewport();
	name = "component";
	_isSelected = false;
	_isVisible = true;
	backgroundColor = NULL;
	selectedBackgroundColor = NULL;
	keyboardListener = NULL;
	mouseListener = NULL;
}

SDLComponent::SDLComponent(int xpos, int ypos, int w, int h, SDLSurface* surface) : x(xpos), y(ypos), width(w), height(h), sdlSurface(surface)
{
	viewport = new Viewport(x, y, width, height);
	name = "component";
	_isSelected = false;
	_isVisible = true;
	backgroundColor = NULL;
	selectedBackgroundColor = NULL;
	keyboardListener = NULL;
	mouseListener = NULL;
}

SDLComponent::~SDLComponent(void)
{
	delete viewport;
	delete backgroundColor;
	delete selectedBackgroundColor;
	delete keyboardListener;
	delete mouseListener;
}

SDLComponent::ComponentType SDLComponent::getType(void)
{
	return type;
}

void SDLComponent::setName(string name)
{
	this->name = name;
}

string SDLComponent::getName(void)
{
	return name;
}

void SDLComponent::setX(int x)
{
	this->x = x;
}

int SDLComponent::getX(void)
{
	return x;
}

void SDLComponent::setY(int y)
{
	this->y = y;
}

int SDLComponent::getY(void)
{
	return y;
}

void SDLComponent::setWidth(int width)
{
	this->width = width;
}

int SDLComponent::getWidth(void)
{
	return width;
}

void SDLComponent::setHeight(int height)
{
	this->height = height;
}

int SDLComponent::getHeight(void)
{
	return height;
}

Viewport* SDLComponent::getViewport(void)
{
	return viewport;
}

void SDLComponent::show(void)
{
	_isVisible = true;
}

void SDLComponent::hide(void)
{
	_isVisible = false;
}

bool SDLComponent::isVisible(void)
{
	return _isVisible;
}

void SDLComponent::select(void)
{
	_isSelected = true;
}

void SDLComponent::unSelect(void)
{
	_isSelected = false;
}

bool SDLComponent::isSelected(void)
{
	return _isSelected;
}

void SDLComponent::updateViewport(Dimension* d)
{
	viewport->setX(d->getX());
	viewport->setY(d->getY());
	viewport->setWidth(d->getWidth());
	viewport->setHeight(d->getHeight());
}

void SDLComponent::setMouseListener(MouseListener* mouseListener)
{
	this->mouseListener = mouseListener;
}

void SDLComponent::setKeyboardListener(KeyboardListener* keyboardListener)
{
	this->keyboardListener = keyboardListener;
}

Color* SDLComponent::getBackgroundColor(void)
{
	return backgroundColor;
}

void SDLComponent::setBackgroundColor(Color* color)
{
	backgroundColor = color;
}

void SDLComponent::setSelectedBackgroundColor(Color* color)
{
	selectedBackgroundColor = color;
}

void SDLComponent::processEvent(SDLEvent* sdlEvent)
{
	if (isHandleKeyboardEvent(sdlEvent))
	{
		SDLKeyboardEvent keyboardEvent = SDLKeyboardEvent(sdlEvent);
		keyboardEvent.setSource(this);
		this->keyboardListener->processKeyboardEvent(&keyboardEvent);
	}
	else if (isHandleMouseEvent(sdlEvent))
	{
		SDLMouseEvent mouseEvent = SDLMouseEvent(sdlEvent);
		mouseEvent.setSource(this);
		if (mouseEvent.getState() == SDLMouseEvent::BUTTON_PRESSED)
		{
			this->mouseListener->processMouseButtonPressed(&mouseEvent);
		}
		else if (mouseEvent.getState() == SDLMouseEvent::BUTTON_RELEASED)
		{
			this->mouseListener->processMouseButtonReleased(&mouseEvent);
		}
	}
}

bool SDLComponent::isHandleKeyboardEvent(SDLEvent* sdlEvent)
{
	bool isHandle = false;
	if (sdlEvent->getType() == SDLEvent::KEYBOARD_EVENT_TYPE && keyboardListener != NULL)
	{
		isHandle = true;
	}
	return isHandle;
}

bool SDLComponent::isHandleMouseEvent(SDLEvent* sdlEvent)
{
	bool isHandle = false;
	if (sdlEvent->getType() == SDLEvent::MOUSE_EVENT_TYPE && mouseListener != NULL)
	{
		SDLMouseEvent* mouseEvent = static_cast<SDLMouseEvent*>(sdlEvent);
		if (mouseEvent->getX() >= x && mouseEvent->getX() <= x+width &&
			mouseEvent->getY() >= y && mouseEvent->getY() <= y+height)
		{
			isHandle = true;
		}
	}
	return isHandle;
}

Dimension SDLComponent::clipToViewport(void)
{
	int clippedWidth = width;
	int clippedHeight = height;
	int widthDiff = (x+width) - (viewport->getX()+viewport->getWidth());
	if (x < viewport->getX()+viewport->getWidth() && widthDiff > 0)
	{
		clippedWidth -= widthDiff;
	}
	int heightDiff = (y+height) - (viewport->getY()+viewport->getHeight());
	if (y < viewport->getY()+viewport->getHeight() && heightDiff > 0)
	{
		clippedHeight -= heightDiff;
	}

	Dimension clippedViewport(x, y, clippedWidth, clippedHeight);
	return clippedViewport;
}
