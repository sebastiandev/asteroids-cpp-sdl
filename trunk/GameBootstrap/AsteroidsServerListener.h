#ifndef _ASTEROIDSSERVERLISTENER_H_
#define _ASTEROIDSSERVERLISTENER_H_

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "concurrent\Runnable.h"
#include "Bootstrap.h"
#include "net\TCPSocket.h"
#include "AsteroidsMsg.h"
#include "..\GameModel\model\Asteroid.h"
#include "..\GameModel\model\Ship.h"
#include "..\Util\UTimer.h"

class AsteroidsServerListener : public concurrent::Runnable
{
public:
	AsteroidsServerListener(net::TCPSocket *socket, bool &isConnected, Bootstrap *clientHandler);
	~AsteroidsServerListener(void);

	DWORD run(void);

	void checkConnection();

private:

	net::TCPSocket  *server;
	//std::shared_ptr<AsteroidsClient> handler;
	Bootstrap *handler;

	bool isConnected;
	long lastUpdate;
	util::UTimer<AsteroidsServerListener> *timer;

};

#endif