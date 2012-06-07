#ifndef _SCENE_H_
#define _SCENE_H_

#include "Bullet.h"
#include "Bonus.h"
#include "Asteroid.h"
#include "Ship.h"
#include "ISceneObserver.h"
#include "Constants.h"
#include <list>
#include "..\..\Util\Logger.h"
#include "..\..\Util\Utils.h"
#include <sstream>
#include <string>
#include <algorithm>
#include <map>

using namespace util;

namespace model
{

class Scene
{
public:
	Scene(int, int);
	virtual ~Scene(void);

	void setObserver(ISceneObserver*);

	void initialize();

	void setAsteroids(list<Asteroid*>);

	list<Asteroid*> getAsteroids(void) { return asteroids;}
	list<Ship*>     getShips    ();
	list<Bullet*>   getBullets  () { return bullets;}
	list<Bonus*>    getBonus  () { return bonus;}

	void  addShip(std::string id, Ship*);

	void        setBackground(string filePath) { background = filePath;}
	std::string getBackground() { return background;}

	int   getWidth ();
	int   getHeight();

	void  accelerateShip   (string shipId="1");
	void  stopAcceleration (string shipId="1");
	void  rotateShipToLeft (string shipId="1");
	void  rotateShipToRight(string shipId="1");
	void  stopRotation     (string shipId="1");

	void  addBullet(double startTime, string shipId="1");
	void  addBonus(double startTime, int x, int y);

	void  update(double);

	std::string toString();

	void randomizeShipsPosition();
	
private:
	int  generateId();
	void checkBordersAndEntityPosition(Entity* e);
	bool defineShipPosition(Ship* ship, int pos);

	ISceneObserver* observer;
	list<Asteroid*> asteroids;
	list<Bullet*> bullets;
	list<Bonus*> bonus;
	map<string, Ship*> ships;

	string background;

	int width;
	int height;		
};
};

#endif
