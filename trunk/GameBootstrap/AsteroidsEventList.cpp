#include "AsteroidsEventList.h"

using namespace std;
using namespace concurrent;

AsteroidsEventList::AsteroidsEventList(void)
{
}


AsteroidsEventList::~AsteroidsEventList(void)
{
}

void AsteroidsEventList::addEvent(AsteroidsEvent e)
{
	Lock lock(this->mutex);
	events.push_back(e);
}

int AsteroidsEventList::size()
{
	return events.size();
}

AsteroidsEvent AsteroidsEventList::getLastEvent(bool remove)
{
	Lock lock(this->mutex);

	AsteroidsEvent e = events.front();
	if (remove)
		events.pop_front();

	return e;
}

list<AsteroidsEvent> AsteroidsEventList::removeAll()
{
	Lock lock(this->mutex);
	
	list<AsteroidsEvent> list(events.begin(), events.end());
	events.clear();
	return list;
}
