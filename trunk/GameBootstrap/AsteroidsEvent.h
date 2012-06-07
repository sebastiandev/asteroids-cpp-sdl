#ifndef _ASTEROIDSEVENT_H_
#define _ASTEROIDSEVENT_H_

#include "model\GameEvent.h"
#include <sstream>

using namespace model;

class AsteroidsEvent : public GameEvent
{
public:
	AsteroidsEvent(void) {}
	AsteroidsEvent(int type) { this->type = type; }
	AsteroidsEvent(int type, int clientId) { this->type = type; this->client = clientId;}
	virtual void setClientId(int id) { this->client = id; }
	virtual int getType(void) { return type;}
	virtual int getClientId(void) { return client;}
	virtual string getClientIdStr(void) { std::stringstream idstr; idstr << client; return idstr.str();}
private:
	int type, client;
};

#endif