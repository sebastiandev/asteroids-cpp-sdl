#include "Viewport.h"

using namespace sdl;

Viewport::Viewport(void)
{
}

Viewport::Viewport(int xpos, int ypos, int w, int h) : Dimension(xpos, ypos, w, h)
{
}

Viewport::~Viewport(void)
{
}

void Viewport::setX(int x)
{
	this->x = x;
}

void Viewport::setY(int y)
{
	this->y = y;
}

void Viewport::setWidth(int width)
{
	this->width = width;
}

void Viewport::setHeight(int height)
{
	this->height = height;
}
