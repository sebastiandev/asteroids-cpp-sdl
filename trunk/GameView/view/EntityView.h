#ifndef _ENTITYVIEW_H_
#define _ENTITYVIEW_H_

#include "../sdl/SDLSurface.h"
#include "../../GameModel/model/Entity.h"
#include <string>

using namespace std;
using namespace model;
using namespace sdl;

namespace view
{
class EntityView
{
public:
	EntityView(Entity *entity, SDLSurface* parentSurface);
	EntityView(Entity *entity, SDLSurface* parentSurface, int width, int height);
	EntityView(Entity *entity, SDLSurface* parentSurface, SDLSurface* srfc);
	virtual ~EntityView();

	virtual void   setPosition(double x, double y);
	virtual double getX(void);
	virtual double getY(void);

	virtual double getWidth();
	virtual double getHeight();

	virtual void paint(void);
	Entity* getEntity(void);

protected:

	virtual void init(Entity* entity, SDLSurface* parentSurface);
	virtual void checkAndPaintEntityOnEdge(double rotatedX, double rotatedY);

	Entity*     entity;
	SDLSurface* surface;
	SDLSurface* parentSurface;
	double      lastDirection;
};
};

#endif
