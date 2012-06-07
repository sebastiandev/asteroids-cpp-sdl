#ifndef _ASTEROIDSCLIENT_H_
#define _ASTEROIDSCLIENT_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "model\GameClient.h"
#include "model\GameEvent.h"
#include "net\TCPSocket.h"
#include "net\SocketException.h"
#include "concurrent\Thread.h"
#include "AsteroidsServerListener.h"
#include "concurrent\Runnable.h"
#include "concurrent\Thread.h"
#include "AsteroidsMsg.h"
#include "AsteroidsEventList.h"
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <memory>

class Bootstrap;
class AsteroidsServerListener;

using namespace model;
using namespace concurrent;
using namespace net;
using namespace std;

class AsteroidsClient : public GameClient, Runnable
{
public:
	AsteroidsClient(void);
	AsteroidsClient(Bootstrap* controller, string ip, int port, string selectedShip);
	virtual ~AsteroidsClient(void);
	virtual void start(string ip, int port, string selectedShip);
	virtual void sendEvent(GameEvent::GameEventType);
	virtual void quit(void);
	virtual string getSceneFilename() { return sceneFileName;}
private:
	DWORD run(void);
	void sendStatus(std::string status);
	void checkConnection();
	Bootstrap* controller;
	AsteroidsServerListener* listener;
	TCPSocket client;
	bool isPlaying;
	string ip, selectedShip, sceneFileName;
	int port;
};

#endif