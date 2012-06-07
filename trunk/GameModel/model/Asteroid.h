#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "Entity.h"
#include "AsteroidType.h"

namespace model
{
class Asteroid : public Entity
{
public:
	Asteroid(AsteroidType*);
	Asteroid(int id, AsteroidType* type, const Point &position, double direction, double rotation, double velocity);

	virtual ~Asteroid(void);

	AsteroidType* getType(void);

	virtual double getVelocity();

	virtual string getImagePath(void);
	virtual void   setImagePath(string);
	void    updatePositions(double);

private:
	AsteroidType* type;	
};
};

#endif
