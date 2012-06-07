#include "AsteroidsServerListener.h"
#include "net\SocketException.h"
#include "concurrent\Thread.h"
#include <iostream>

using namespace net;
using namespace std;
using namespace concurrent;

AsteroidsServerListener::AsteroidsServerListener(net::TCPSocket *socket, bool &isConnected, Bootstrap *clientHandler)
{
	server  = socket;	
	
	// Tiene que crear un shared_pointer y que no llame al delete del objeto
	// porque no es el dueño. Usa una funcion lambda que no hace nada
	//handler.reset(clientHandler, [](AsteroidsClient* ptr) { });
	handler = clientHandler;

	this->isConnected = isConnected;
	this->lastUpdate = 0;
	timer = new UTimer<AsteroidsServerListener>(30000);
}


AsteroidsServerListener::~AsteroidsServerListener(void)
{
	timer->stop();
	delete timer;
}

DWORD AsteroidsServerListener::run(void)
{
	AsteroidsMsg serverMsg;

	// Lanzo el timer para que cada 20 segundos chequee la conexion llamando al metodo "checkConnection"
	timer->setCallback(this, &AsteroidsServerListener::checkConnection);
	Thread tt(timer);
	tt.start();

	while (isConnected)
	{
		try
		{
			string update = server->doReceive(AsteroidsMsg::getControlCharacter());
			if (update.compare("QUIT") == 0)
			{
				cout << "[AsteroidsServerListener] server sent QUIT" << endl;
				server->doClose();
				break;
			}			

			lastUpdate = clock();
			serverMsg.reset();
			serverMsg.setData(update);

			handler->updateEntities(serverMsg.getAsteroidsData(), serverMsg.getShipsData(), serverMsg.getBulletsData(),serverMsg.getBonusData());
			server->doSend("OK;");
		}
		catch (SocketException&)
		{
			cout << "[AsteroidsServerListener] Error reading server socket..." << endl;
			server->doClose();
			break;
		}
		catch (...)
		{
			cout << "[AsteroidsServerListener] Uexpected error" << endl;
			server->doClose();
			break;
			//return 1;
		}
	}

	cout << "[AsteroidsServerListener] Quiting listener!" << endl;
	handler->quitGame();
	isConnected = false;
	timer->stop();
	tt.stop();

	return 0;
}

void AsteroidsServerListener::checkConnection()
{
	cout << "[AsteroidsServerListener] Checking connection..." << endl;

	long timeSinceLastUpdate = (clock() - lastUpdate)/1000;
	if (timeSinceLastUpdate > 15)
	{
		cout << "[AsteroidsServerListener] Last update was " << timeSinceLastUpdate << " seconds ago. Connection seems to be lost." << endl;
		server->doClose();
		isConnected = false;
		timer->stop();
		handler->quitGame();
	}
}
