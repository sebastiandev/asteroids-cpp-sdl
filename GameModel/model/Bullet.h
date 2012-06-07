#ifndef _BULLET_H_
#define _BULLET_H_

#include "Entity.h"

namespace model
{
class Bullet : public Entity
{
public:
	Bullet(void);
	Bullet(int id, std::string image, const Point &position, int duration, double startTime);
	virtual ~Bullet(void);
	
	string getImagePath(void);
	void   setImagePath(string path);

	void   setDuration(int);
	int    getDuration();
	void   setStartTime(double);
	double getStartTime();
	void   updatePositions(double);

private:
	string imagePath;
	double startTime;
	int    duration;
};
};

#endif
