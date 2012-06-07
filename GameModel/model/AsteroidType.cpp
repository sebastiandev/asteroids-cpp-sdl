#include "AsteroidType.h"

using namespace model;

AsteroidType::AsteroidType(string name) : name(name)
{
	this->width = 0;
	this->height = 0;
	this->rotationAngle = 0;
}

AsteroidType::~AsteroidType(void)
{
}

string AsteroidType::getName(void)
{
	return name;
}

void AsteroidType::setImagePath(string path)
{
	this->imagePath = path;
}

string AsteroidType::getImagePath(void)
{
	return imagePath;
}

void AsteroidType::setWidth(int width)
{
	this->width = width;
}

int model::AsteroidType::getWidth(void)
{
	return width;
}

void AsteroidType::setHeight(int height)
{
	this->height = height;
}

int model::AsteroidType::getHeight(void)
{
	return height;
}

void AsteroidType::setRotationAngle(int angle)
{
	this->rotationAngle = angle;
}

int AsteroidType::getRotationAngle(void)
{
	return rotationAngle;
}
