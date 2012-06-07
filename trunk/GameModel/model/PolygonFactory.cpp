#include "PolygonFactory.h"
#include "Point.h"

using namespace model;

PolygonFactory& PolygonFactory::instance()
{
	static PolygonFactory instance;
	return instance;
}

Polygon* PolygonFactory::createSquare(const Point &position, short positionLocation, int size)
{
	return createRectangle(position, positionLocation, size, size);
}

Polygon* PolygonFactory::createRectangle(const Point &position, short positionLocation, int width, int height)
{
	Point topLeft, topRight, bottomLeft, bottomRight;	
	
	if (positionLocation == PF_Center)
	{
		topLeft     = Point(position.x() - width/2, position.y() - height/2);
		topRight    = Point(position.x() + width/2, position.y() - height/2);
		bottomLeft  = Point(position.x() - width/2, position.y() + height/2);
		bottomRight = Point(position.x() + width/2, position.y() + height/2);
	}
	else if (positionLocation == PF_TopLeft)
	{
		topLeft     = Point(position.x(), position.y());
		topRight    = Point(position.x() + width, position.y());
		bottomLeft  = Point(position.x(), position.y() + height);
		bottomRight = Point(position.x() + width, position.y() + height);
	}

	Polygon *p = new Polygon();
	p->addVertex(topLeft);
	p->addVertex(topRight);
	p->addVertex(bottomRight);
	p->addVertex(bottomLeft);
	return p;
}
Polygon* PolygonFactory::createTriangle(const Point &position, short positionLocation, int width, int height)
{
	Point leftCorner, topCorner, rightcorner;
	
	if (positionLocation == PF_Center)
	{
		leftCorner  = Point(position.x() - width/2, position.y() + height/2);
		topCorner   = Point(position.x(), position.y() - height/2);
		rightcorner = Point(position.x() + width/2, position.y() + height/2);
	}
	else if (positionLocation == PF_TopLeft)
	{
		leftCorner   = Point(position.x(), position.y() + height);
		topCorner    = Point(position.x() + width/2, position.y());
		rightcorner  = Point(position.x() + width, position.y() + height);
	}

	Polygon *p = new Polygon();
	p->addVertex(leftCorner);
	p->addVertex(topCorner);
	p->addVertex(rightcorner);
	return p;
}
Polygon* PolygonFactory::createCircle(const Point &position, short positionLocation, int vertices)
{
	return NULL;
}
Polygon* PolygonFactory::createL(const Point &position, short positionLocation, int width, int height, int verticalWidth, int horizontalHeight)
{
	return NULL;
}
