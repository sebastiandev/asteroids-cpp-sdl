#include "Bonus.h"

using namespace model;

Bonus::Bonus(void) : Entity()
{	
}

Bonus::~Bonus(void)
{
}

string Bonus::getImagePath(void)
{
	return imagePath;
}

void Bonus::setImagePath(string path)
{
	this->imagePath = path;
}

void Bonus::setStartTime(double start)
{
	this->startTime = start;
}

double Bonus::getStartTime()
{
	return startTime;
}

void Bonus::setCode(char code)
{
	this->code = code;
}

char Bonus::getCode()
{
	return code;
}

void Bonus::updatePositions(double currentTime)
{
}

