#ifndef _GAMECLIENT_H_
#define _GAMECLIENT_H_

#include "GameEvent.h"
#include <string>

using namespace std;

namespace model
{
class GameClient
{
public:
	GameClient(void);
	virtual ~GameClient(void);
	virtual void start(string ip, int port, string selectedShip)=0;
	virtual void sendEvent(GameEvent::GameEventType)=0;
	virtual void quit(void)=0;
	virtual string getSceneFilename(void)=0;
};
};

#endif