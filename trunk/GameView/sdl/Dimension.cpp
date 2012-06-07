#include "Dimension.h"

using namespace sdl;

Dimension::Dimension(void) : x(0), y(0), width(0), height(0)
{
}

Dimension::Dimension(int xpos, int ypos, int w, int h) : x(xpos), y(ypos), width(w), height(h)
{
}

Dimension::~Dimension(void)
{
}

int Dimension::getX(void)
{
	return x;
}

int Dimension::getY(void)
{
	return y;
}

int Dimension::getWidth(void)
{
	return width;
}

int Dimension::getHeight(void)
{
	return height;
}

Dimension* Dimension::intersect(Dimension* d)
{
	int intersectx = 0, intersectWidth = 0;
	if (d->getX() >= x && d->getX()+d->getWidth() <= x+width)
	{
		intersectx = d->getX();
		intersectWidth = d->getWidth();
	}
	else if (x > d->getX() && x+width < d->getX()+d->getWidth())
	{
		intersectx = x;
		intersectWidth = width;
	}
	else if (d->getX() > x && d->getX() < x+width && d->getX()+d->getWidth() > x+width)
	{
		intersectx = d->getX();
		intersectWidth = x+width-d->getX();
	}
	else if (d->getX() < x && d->getX()+d->getWidth() > x && d->getX()+d->getWidth() < x+width)
	{
		intersectx = x;
		intersectWidth = d->getX()+d->getWidth()-x;
	}

	int intersecty = 0, intersectHeight = 0;
	if (d->getY() >= y && d->getY()+d->getHeight() <= y+height)
	{
		intersecty = d->getY();
		intersectHeight = d->getHeight();
	}
	else if (y > d->getY() && y+height < d->getY()+d->getHeight())
	{
		intersecty = y;
		intersectHeight = height;
	}
	else if (d->getY() > y && d->getY() < y+height && d->getY()+d->getHeight() > y+height)
	{
		intersecty = d->getY();
		intersectHeight = y+height-d->getY();
	}
	else if (d->getY() < y && d->getY()+d->getHeight() > y && d->getY()+d->getHeight() < y+height)
	{
		intersecty = y;
		intersectHeight = d->getY()+d->getHeight()-y;
	}
	Dimension* intersectDimension = new Dimension(intersectx, intersecty, intersectWidth, intersectHeight);
	return intersectDimension;
}
