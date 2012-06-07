#include "Asteroid.h"

using namespace model;

Asteroid::Asteroid(AsteroidType* type) : type(type)
{
}

Asteroid::Asteroid(int id, AsteroidType* type, const Point &position, double direction, double rotation, double velocity)
{
	this->id       = id;
	this->type     = type;
	this->x        = position.x();
	this->y        = position.y();
	this->rotation = rotation;
	this->velocity = velocity;
	this->directionOfVelocity = direction;
}

Asteroid::~Asteroid(void)
{
}

AsteroidType* Asteroid::getType(void)
{
	return type;
}

string Asteroid::getImagePath(void)
{
	return type->getImagePath();
}

void Asteroid::setImagePath(string path)
{
	return type->setImagePath(path);
}

double Asteroid::getVelocity()
{
	return velocity;
}

void Asteroid::updatePositions(double currentTime)
{
	double deltaTime;
	double deltaDirection;

	deltaTime = currentTime - this->currentTime;
	this->currentTime = currentTime;
	
	deltaDirection = (this->getVelocity() * deltaTime);
	if (deltaDirection <= 0)
		deltaDirection = 0;

	this->directionModul = deltaDirection;
	
	this->move();
}