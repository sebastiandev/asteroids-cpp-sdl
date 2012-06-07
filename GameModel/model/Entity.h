#ifndef _ENTITY_H_
#define _ENTITY_H_

#define _USE_MATH_DEFINES

#include <string>

#include "Constants.h"
#include "Polygon.h"

using namespace std;

namespace model
{
class Entity
{
public:
	Entity(void);
	virtual ~Entity(void);

	virtual string getImagePath(void) = 0;
	virtual void   setImagePath(string) = 0;
	virtual void   updatePositions(double currentTime) = 0;

	int  getId();
	void setId(int id) { this->id = id;}

	Point    getPosition();

	Polygon* getPolygon();
	void     setPolygon(Polygon* p);

	virtual void   setX(double);
	virtual double getX(void);
	virtual void   setY(double);
	virtual double getY(void);
    virtual void   setPosition(double x, double y);
	virtual void   setRotation(double);
	virtual double getRotation(void);
	virtual void   setDirectionOfVelocity(double);
	virtual double getDirectionOfVelocity(void);
	virtual void   setVelocity(double);
	virtual double getVelocity(void);

protected:

	virtual void move(void);
	
	auto_ptr<Polygon> polygon;

	int    id;
	double x;
	double y;
	double velocity;
	double rotation;
	double directionOfVelocity;
	double currentTime;
	double directionModul;
};
};
#endif
