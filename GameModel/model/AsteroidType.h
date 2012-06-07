#ifndef _ASTEROIDTYPE_H_
#define _ASTEROIDTYPE_H_

#include <string>

using namespace std;


namespace model
{
class AsteroidType
{
public:
	AsteroidType(string);
	virtual ~AsteroidType(void);

	string getName(void);
	void   setImagePath(string);
	string getImagePath(void);
	void   setWidth(int);
	int    getWidth(void);
	void   setHeight(int);
	int    getHeight(void);
	void   setRotationAngle(int);
	int    getRotationAngle(void);

private:
	string name;
	string imagePath;
	int width;
	int height;
	int rotationAngle;
};
};

#endif
