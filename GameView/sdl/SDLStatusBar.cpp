#include "SDLStatusBar.h"

using namespace sdl;

SDLStatusBar::SDLStatusBar(SDLSurface* surface) : SDLComponent(surface)
{
	this->name = "statusbar";
	this->type = SDLComponent::STATUSBAR;
	label = new SDLLabel(" ", surface);
	initialize();
}

SDLStatusBar::SDLStatusBar(int size, SDLSurface* surface) : SDLComponent(surface)
{
	this->name = "statusbar";
	this->type = SDLComponent::STATUSBAR;
	label = new SDLLabel(" ", size, surface);
	initialize();
}

SDLStatusBar::~SDLStatusBar(void)
{
	delete label;
}

void SDLStatusBar::draw(void)
{
	boxRGBA(sdlSurface->getSurface(), x, y, x+width, y+height, 232, 232, 232, 255);
	label->draw();
	lineRGBA(sdlSurface->getSurface(), x, y, x+width, y, 0, 0, 0, 255);
}

void SDLStatusBar::setStatusText(string statusText)
{
	label->setText(statusText);
}

void SDLStatusBar::initialize(void)
{
	x = 0;
	y = sdlSurface->getHeight()-label->getHeight()-10;
	width = sdlSurface->getWidth();
	height = sdlSurface->getHeight()-y;
	viewport->setX(x);
	viewport->setY(y);
	viewport->setWidth(width);
	viewport->setHeight(height);

	label->setX(x+10);
	label->setY(y+5);
	label->setWidth(width-10);

	Viewport* labelViewport = label->getViewport();
	labelViewport->setX(x);
	labelViewport->setY(y);
	labelViewport->setWidth(width);
	labelViewport->setHeight(height);
}
