#ifndef _ASTEROIDSEVENTLIST_H_
#define _ASTEROIDSEVENTLIST_H_

#include <list>
#include "concurrent\Lock.h"
#include "AsteroidsEvent.h"

class AsteroidsEventList
{
public:
	AsteroidsEventList(void);
	~AsteroidsEventList(void);

	void addEvent(AsteroidsEvent e);

	int                       size        ();
	std::list<AsteroidsEvent> removeAll   ();
	AsteroidsEvent            getLastEvent(bool remove=true);

private:
	concurrent::Mutex mutex;
	std::list<AsteroidsEvent> events;

};

#endif