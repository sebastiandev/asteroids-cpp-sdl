#include "Entity.h"
using namespace model;

Entity::Entity(void)
{
	static int counter = 0;

	id = counter++;
	rotation = 0.0;
	directionOfVelocity = 0.0;
	velocity = 0.0;
	directionModul = 0.0;
	currentTime = 0.0;
}

Entity::~Entity(void)
{
}

Point Entity::getPosition()
{
	return Point(x, y);
}

Polygon* Entity::getPolygon()
{
	return polygon.get();
}
void Entity::setPolygon(Polygon* p)
{
	polygon.reset(p);
}

int Entity::getId()
{
	return id;
}
void Entity::setX(double x)
{
	this->x = x;
}

double Entity::getX(void)
{
	return x;
}

void Entity::setY(double y)
{
	this->y = y;
}

double Entity::getY(void)
{
	return y;
}

void Entity::setPosition(double x, double y)
{
	this->x = x;
	this->y = y;
}

void Entity::setVelocity(double velocity)
{
	this->velocity = velocity;
}

double Entity::getVelocity(void)
{
	return velocity;
}

void Entity::setRotation(double rotation)
{
	this->rotation = rotation;
}

double Entity::getRotation(void)
{
	return this->rotation;
}

void Entity::setDirectionOfVelocity(double direction)
{
	this->directionOfVelocity = direction;
}

double Entity::getDirectionOfVelocity(void)
{
	return this->directionOfVelocity;
}

void Entity::move()
{
	//Angulo entre 0 y 90, para Rotozoom la rotacion es en sentido anti-horario.
	//45 grados significa segundo cuadrante (arriba a la izquierda)
	if (directionOfVelocity >= 0 && directionOfVelocity <= 90)
	{
		y -= this->directionModul * cos(directionOfVelocity * M_PI/180);
		x -= this->directionModul * sin(directionOfVelocity * M_PI/180);
	}
	//135 grados significa tercer cuadrante (abajo a la izquierda)
	else if (directionOfVelocity > 90 && directionOfVelocity <= 180)
	{
		y += this->directionModul * cos((180 - directionOfVelocity) * M_PI/180);
		x -= this->directionModul * sin((180 - directionOfVelocity) * M_PI/180);	
	}
	//225 grados significa cuarto cuadrante (abajo a la derecha)
	else if (directionOfVelocity > 180 && directionOfVelocity <= 270)
	{
		y += this->directionModul * sin((270 - directionOfVelocity) * M_PI/180);
		x += this->directionModul * cos((270 - directionOfVelocity) * M_PI/180);
	}
	//315 grados significa primer cuadrante (arriba a la derecha)
	else if (directionOfVelocity > 270 && directionOfVelocity <= 360)
	{
		y -= this->directionModul * cos((360 - directionOfVelocity) * M_PI/180);
		x += this->directionModul * sin((360 - directionOfVelocity) * M_PI/180);	
	}
}
