#include "Ship.h"

using namespace model;

Ship::Ship(void) : Entity()
{
	this->rotationVelocity        = 0;
	this->maximumVelocity         = 0;
	this->propulsion              = 0;
	this->friction                = 0;
	this->bulletTimeout           = 0;
	this->aceleration             = 0;
	this->currentRotationVelocity = 0;
	this->rotation                = 0.0;
	this->directionOfVelocity     = 0.0;
}

Ship::Ship(int id, const std::string& image, const Point &position, int rotationVelocity,  int maxVelocity, int propulsion, int friction, int bulletTimeOut)
{
	this->id        = id;
	this->imagePath = image;
	this->x         = position.x();
	this->y         = position.y();

	this->rotationVelocity        = rotationVelocity;
	this->maximumVelocity         = maxVelocity;
	this->propulsion              = propulsion;
	this->friction                = friction;
	this->bulletTimeout           = bulletTimeOut;
	this->aceleration             = 0;
	this->currentRotationVelocity = 0;
	this->rotation                = 0.0;
	this->directionOfVelocity     = 0.0;
}

Ship::~Ship(void)
{
}

string Ship::getImagePath(void)
{
	return imagePath;
}

void Ship::setImagePath(string path)
{
	this->imagePath = path;
}

void Ship::setRotationVelocity(int velocity)
{
	this->rotationVelocity = velocity;
}

int Ship::getRotationVelocity(void)
{
	return rotationVelocity;
}

void Ship::setMaximumVelocity(int velocity)
{
	this->maximumVelocity = velocity;
}

int Ship::getMaximumVelocity(void)
{
	return maximumVelocity;
}

void Ship::setPropulsion(int propulsion)
{
	this->propulsion = propulsion;
}

int Ship::getPropulsion(void)
{
	return propulsion;
}

void Ship::setFriction(int friction)
{
	this->friction = friction;
}

int Ship::getFriction(void)
{
	return friction;
}

void Ship::setBulletTimeout(int timeout)
{
	this->bulletTimeout = timeout;
}

int Ship::getBulletTimeout(void)
{
	return bulletTimeout;
}

//ROTATION_STEP es una constante para definir el paso (pixeles) de avance
void Ship::rotateLeft()
{	
	currentRotationVelocity = rotationVelocity;
	//direction +=  rotationVelocity;
	//Condicion para que el angulo quede siempre entre 0 y 360 
	//aunque a la nave se la gire continuamente
	//if (direction > 360)
	//	direction = direction - 360;
}

//ROTATION_STEP es una constante para definir el paso (pixeles) de avance
void Ship::rotateRight()
{
	currentRotationVelocity = -rotationVelocity;
	//direction -= rotationVelocity;
	//Condicion para que el angulo quede siempre entre 0 y 360 
	//aunque a la nave se la gire continuamente
	//if (direction < 0)
	//	direction = direction + 360;
}

void Ship::stopRotation()
{
	this->currentRotationVelocity = 0;
}

void Ship::acelerate(void)
{
	this->aceleration = this->propulsion;
}

void Ship::stopAceleration()
{
	this->aceleration = 0;
}

bool Ship::isAcelerated (void)
{
	return (this->aceleration > 0);
}

void Ship::setLife(int life)
{
	this->life = life;
}

int Ship::getLife()
{
	return life;
}

void Ship::setNumberOfLifes(int numberOfLifes)
{
	this->numberOfLifes = numberOfLifes;
}

int Ship::getNumberOfLifes()
{
	return numberOfLifes;
}

void Ship::updatePositions(double currentTime)
{
	double currentVelocity;	
	double deltaDirection;

	double deltaTime = currentTime - this->currentTime;
	this->currentTime = currentTime;

	double angleDiff = this->directionOfVelocity - this->rotation;

	//Agrego el coseno de la diferencia de los angulos de velocidad y rotacion, para q frene al comienzo de la rotacion si no coinciden las direcciones.
	if (isAcelerated()) //Mientras se este acelerando no aplicamos friccion.
		currentVelocity = (this->getVelocity() * cos(angleDiff)) + (deltaTime * (this->aceleration));
	else
		currentVelocity = this->getVelocity() + (deltaTime * (this->aceleration - this->friction));
	
	if (currentVelocity < 0)
	{
		currentVelocity = 0;
	}
	if (currentVelocity > this->maximumVelocity)
	{
		currentVelocity = this->maximumVelocity;
	}
		
	//dx = (V0 * dt) + 1/2 dt2 * (aceleracion - friccion)
	deltaDirection =  (this->getVelocity() * deltaTime) + (0.5 * pow(deltaTime,2) * (this->aceleration - this->friction));
	if (deltaDirection < 0)
		deltaDirection = 0;
	
	this->setVelocity(currentVelocity); 
	this->directionModul = deltaDirection;
	
	//dAngulo = (360 / Segundos por vuelta) * dt
	if (this->currentRotationVelocity != 0)
		this->rotation += ((360) / this->currentRotationVelocity) * deltaTime;

	if (this->rotation < 0)
		this->rotation = this->rotation + 360;

	if (this->rotation > 360)
		this->rotation = this->rotation - 360;

	if (this->isAcelerated())
		this->directionOfVelocity = this->rotation;

		this->move();
}

string Ship::getAcceleratedImagePath(void)
{
	int pos = this->imagePath.find(".");
	string acceleratedPath = this->imagePath.substr(0,pos) + "_on.png";
	return acceleratedPath;
}