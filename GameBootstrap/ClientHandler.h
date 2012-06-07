#ifndef _CLIENTHANDLER_H_
#define _CLIENTHANDLER_H_

#include "concurrent\Runnable.h"
#include "net\TCPSocket.h"
#include "..\GameModel\model\Ship.h"
#include "AsteroidsMsg.h"
#include "AsteroidsEventList.h"

#include <string>
#include <list>
#include <map>


class ClientHandler : public concurrent::Runnable
{
public:

	typedef enum status { IDLE, INITIALIZING_CLIENT, WAITING_TO_START, LISTENING_TO_CLIENT, DISCONNECTED };

	ClientHandler(net::TCPSocket *cliente, int id, AsteroidsEventList *eventQueue);
	~ClientHandler(void);

	DWORD run(void);

	void setSceneFile(std::string sceneFile) { this->sceneFile = sceneFile;}
	void setImages   (std::string filesDir, std::list<std::string> images) { this->filesDir = filesDir; this->images = images;}
	
	void sendUpdate(AsteroidsMsg &update);
	void sendQuit  ();

	bool isReadyForNextUpdate() { return readyForNextUpdate;}

	bool isReady        () { return (clientStatus == WAITING_TO_START);}
	void setReadyToStart() { clientStatus = LISTENING_TO_CLIENT;}
	int  getStatus      () { return clientStatus;}

	void stop();

	std::string  getClientId  () { return clientId;}
	model::Ship* getClientShip() { return ship;}

private:

	void processClientMsg(std::string clientUpdate);

	net::TCPSocket         *cliente;
	AsteroidsEventList     *eventQueue;
	std::string            filesDir;
	std::list<std::string> images;
	std::string            sceneFile;
	std::string            clientId;
	model::Ship*           ship;

	bool readyForNextUpdate;
	int id, error, clientStatus;
};

#endif