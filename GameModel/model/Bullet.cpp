#include "Bullet.h"

using namespace model;

Bullet::Bullet(void) : Entity()
{	
}

Bullet::Bullet(int id, std::string image, const Point &position, int duration, double startTime)
{
	this->id        = id;
	this->imagePath = image;
	this->x         = position.x();
	this->y         = position.y();
	this->duration  = duration;
	this->startTime = startTime;
}

Bullet::~Bullet(void)
{
}

string Bullet::getImagePath(void)
{
	return imagePath;
}

void Bullet::setImagePath(string path)
{
	this->imagePath = path;
}

void Bullet::setDuration(int duration)
{
	this->duration = duration;
}

int Bullet::getDuration()
{
	return duration;
}

void Bullet::setStartTime(double start)
{
	this->startTime = start;
}

double Bullet::getStartTime()
{
	return startTime;
}

void Bullet::updatePositions(double currentTime)
{
	double deltaTime;

	deltaTime = currentTime - this->currentTime;
	this->currentTime = currentTime; 

	this->directionModul = BULLET_VELOCITY;
	
	this->move();
}

