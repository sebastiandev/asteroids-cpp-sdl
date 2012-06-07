#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Collision.h"

#include <map>
#include <vector>
#include <list>

namespace model
{

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void addPasiveEntity(model::Entity *entidad);
	void addActiveEntity(model::Entity *entidad);

	void calculateCollisions();

	std::list<Collision> getCollisions();

protected:

	void calculateCollisionsBetween(map<int, model::Entity*> collection1, map<int, model::Entity*> collection2);

	std::list<Collision>      _collisions;
	std::map<int, model::Entity*>    _activeEntities, _passiveEntities;
	map<pair<int, int>, bool> _trackCollisions;
};
};
#endif

