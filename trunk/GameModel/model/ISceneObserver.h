#ifndef _ISCENEOBSERVER_H_
#define _ISCENEOBSERVER_H_

#include "Entity.h"

namespace model
{
class ISceneObserver
{
public:

	virtual void newEntity       (Entity* entity, int width, int height) = 0;
	virtual void newEntity       (Entity* entity) = 0;
	virtual void removedEntity   (Entity* e) = 0;

	virtual int  getEntityWidth  (Entity* e) = 0;
	virtual int  getEntityHeight (Entity* e) = 0;

};
};
#endif