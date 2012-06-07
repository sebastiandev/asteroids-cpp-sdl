#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "Entity.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Bonus.h"

#include "PolygonFactory.h"

namespace model
{

class EntityFactory
{
public:

	typedef enum BulletType   { B_SIMPLE, B_LASER, B_MISIL };
	typedef enum BonusType    { X_CIRCLE, X_TRIANGLE};

	~EntityFactory(){}

	static EntityFactory& instance()
	{
		static EntityFactory instance;
		return instance;
	}

	Ship* createShip(int id, std::string image, const Point &position, int rotationVelocity,  int maxVelocity, int propulsion, int friction, int bulletTimeOut)
	{
		Ship* ship = new Ship(id, image, position, rotationVelocity, maxVelocity, propulsion, friction, bulletTimeOut);
		ship->setPolygon(PolygonFactory::instance().createTriangle(position, PolygonFactory::PF_TopLeft));
		return ship;
	}

	Asteroid* createAsteroid(int id, AsteroidType* type, const Point &position, double direction, double rotation, double velocity)
	{
		Asteroid* asteroid = new Asteroid(id, type, position, direction, rotation, velocity);
		/*
		switch (type->getName())
		{
		case A_CIRCLE:    asteroid->setPolygon(PolygonFactory::instance().createTriangle(position, PolygonFactory::PF_TopLeft));
			              break;
		case A_RECTANGLE: asteroid->setPolygon(PolygonFactory::instance().createRectangle(position, PolygonFactory::PF_TopLeft));
			              break;
		case A_SQUARE:    asteroid->setPolygon(PolygonFactory::instance().createSquare(position, PolygonFactory::PF_TopLeft));
			              break;
		default:          asteroid->setPolygon(PolygonFactory::instance().createSquare(position, PolygonFactory::PF_TopLeft));
			              break;
		}
		*/
		return asteroid;
	}

	Bullet* createBullet(int id, std::string image, const Point &position, int duration, double startTime, BulletType type=B_SIMPLE)
	{
		Bullet* bullet = new Bullet(id, image, position, duration, startTime);
		switch (type)
		{
		case B_SIMPLE:    bullet->setPolygon(PolygonFactory::instance().createRectangle(position, PolygonFactory::PF_TopLeft, 5, 5));
			              break;
		case B_LASER:     bullet->setPolygon(PolygonFactory::instance().createRectangle(position, PolygonFactory::PF_TopLeft, 5, 30));
			              break;
		case B_MISIL:     bullet->setPolygon(PolygonFactory::instance().createRectangle(position, PolygonFactory::PF_TopLeft, 8, 10));
			              break;
		default:          bullet->setPolygon(PolygonFactory::instance().createRectangle(position, PolygonFactory::PF_TopLeft, 5, 5));
			              break;
		}

		return bullet;
	}

	Bonus* createBonus(int id, const Point &position, int code, double startTime, BonusType type=X_CIRCLE)
	{
		Bonus* bonus = new Bonus();
		bonus->setId(id);
		bonus->setStartTime(startTime);
		bonus->setCode(code);

		switch (type)
		{
		case X_CIRCLE:    bonus->setPolygon(PolygonFactory::instance().createCircle(position, PolygonFactory::PF_TopLeft));
			              break;
		case X_TRIANGLE:  bonus->setPolygon(PolygonFactory::instance().createTriangle(position, PolygonFactory::PF_TopLeft));
			              break;
		default:          bonus->setPolygon(PolygonFactory::instance().createCircle(position, PolygonFactory::PF_TopLeft));
			              break;
		}

		return bonus;
	}

protected:

	EntityFactory() {}

};
};
#endif