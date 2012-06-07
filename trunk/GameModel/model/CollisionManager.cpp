#include "CollisionManager.h"
#include "PolygonFactory.h"

#include <algorithm>
#include <iostream>

using namespace std;
using namespace model;

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::addPasiveEntity(Entity *entidad)
{
	_passiveEntities.insert( pair<int, Entity*>(entidad->getId(), entidad) );
}
void CollisionManager::addActiveEntity(Entity *entidad)
{
	_activeEntities.insert( pair<int, Entity*>(entidad->getId(), entidad) );
}

list<Collision> CollisionManager::getCollisions()
{
	return _collisions;
}

void CollisionManager::calculateCollisions()
{
	cout << "Calculando colisiones entre " << _activeEntities.size() + _passiveEntities.size() << " entidades..." << endl;

	_trackCollisions.clear();
	_collisions.clear();

	calculateCollisionsBetween(_activeEntities, _activeEntities);
	calculateCollisionsBetween(_passiveEntities, _activeEntities);
}

void CollisionManager::calculateCollisionsBetween(map<int, Entity*> collection1, map<int, Entity*> collection2)
{
	map<int, Entity*>::iterator it;
	map<int, Entity*>::iterator it2;
	int id1 = -1, id2 = -1;
    
	for (it=collection1.begin(); it!=collection1.end(); it++)
	{
		id1 = it->first;
		Polygon *polygon = it->second->getPolygon();
		if (!polygon) continue;

		for (it2=collection2.begin(); it2!=collection2.end(); it2++)
		{			
			id2 = it2->first;
			if (id1 != id2)
			{
				// si ya existe una colision entre entidad id1 y entidad id2 o al reves, no se vuelve a calcular				
				if (_trackCollisions.find(pair<int, int>(id1, id2)) != _trackCollisions.end() || 
					_trackCollisions.find(pair<int, int>(id2, id1)) != _trackCollisions.end())
				{
					//cout << "ya existe colision entre " << id1 << " y " << id2 << endl;
					continue;
				}

				//cout << "Checking entidad " << id1 << " contra Entidad " << id2 << endl;
				if (!it2->second->getPolygon()) continue;

				vector<Point*>&  points = it2->second->getPolygon()->getVertices();
				vector<Point*>::iterator itPoints;
				for (itPoints=points.begin(); itPoints != points.end(); itPoints++)
				{
					//cout << "Chequeando entidad " << id1 << " con punto (" << (**itPoints).x() << ", " << (**itPoints).y() << ") de entidad " << id2 << endl;
					if (polygon->containsPoint(**itPoints))
					{
						_collisions.push_back(Collision(it->second, it2->second, (**itPoints)));
						_trackCollisions.insert(pair<pair<int, int>, bool>(pair<int, int>(id1, id2), true));
						break;
					}
				}
			}
		}
	}
}

