#ifndef COLLISION_H
#define COLLISION_H

#include "Point.h"
#include "Entity.h"
#include <list>

namespace model
{

class Collision
{
public:
	Collision(){}
	Collision(model::Entity* entidad1, model::Entity* entidad2, Point p)
	{
		this->e1 = entidad1; 
		this->e2 = entidad2; 
		this->_collisionPoint = p;		
	}

	Collision(model::Entity* entidad1, model::Entity* entidad2, int x, int y)
	{
		this->e1 = entidad1; 
		this->e2 = entidad2; 
		this->_collisionPoint.setX(x);
		this->_collisionPoint.setY(y);
	}

	void setCollision(model::Entity* entidad1, model::Entity* entidad2, int x, int y)
	{
		this->e1 = entidad1; 
		this->e2 = entidad2; 
		this->_collisionPoint.setX(x);
		this->_collisionPoint.setY(y);
	}
	
	void setCollision(model::Entity* entidad1, model::Entity* entidad2, Point p)
	{
		this->e1 = entidad1; 
		this->e2 = entidad2; 
		this->_collisionPoint = p;
	}

	model::Entity* getFirstEntity   () { return e1;}
	model::Entity* getSecondEntity  () { return e2;}
	Point          getCollisionPoint() { return _collisionPoint;}

private:

	model::Entity *e1, *e2;
	Point   _collisionPoint;

};
};
#endif;