#ifndef _SHIP_H_
#define _SHIP_H_

#include "Entity.h"

namespace model
{
class Ship : public Entity
{
public:
	Ship(void);
	Ship(int id, const std::string& image, const Point &position, int rotationVelocity,  int maxVelocity, int propulsion, int friction, int bulletTimeOut);

	virtual ~Ship(void);

	void   setImagePath(string);
	string getImagePath(void);

	void setLife(int life);
	int  getLife();
	void setNumberOfLifes(int numberOfLifes);
	int  getNumberOfLifes();

	void setRotationVelocity(int);
	int  getRotationVelocity(void);
	void setMaximumVelocity(int);
	int  getMaximumVelocity(void);
	void setPropulsion(int);
	int  getPropulsion(void);
	void setFriction(int);
	int  getFriction(void);
	void setBulletTimeout(int);
	int  getBulletTimeout(void);
	void rotateLeft(void);
	void rotateRight(void);
	virtual void updatePositions(double currentTime);
	void acelerate(void);
	void stopAceleration(void);
	bool isAcelerated(void);
	void stopRotation(void);	

	bool isRotatingLeft () { return currentRotationVelocity > 0;}
	bool isRotatingRight() { return currentRotationVelocity < 0;}

	string getAcceleratedImagePath(void);

private:
	string imagePath;
	int rotationVelocity;
	int maximumVelocity;
	int propulsion;
	int friction;
	int bulletTimeout;
	int aceleration;
	int currentRotationVelocity;
	int life, numberOfLifes;
};
};

#endif
