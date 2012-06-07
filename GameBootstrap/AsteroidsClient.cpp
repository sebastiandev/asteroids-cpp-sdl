#include "AsteroidsClient.h"

#include "io\Dir.h"
#include "Bootstrap.h"

#define TEMPDIR "tmp\\"

using namespace net;
using namespace std;
using namespace view;
using namespace persistence;
using namespace model;
using namespace io;
using namespace concurrent;

AsteroidsClient::AsteroidsClient(void)
{
	controller = NULL;
	listener  = NULL;
}

AsteroidsClient::AsteroidsClient(Bootstrap *controller, string ip, int port, string selectedShip)
{
	this->controller = controller;
	this->ip = ip;
	this->port = port;
	this->selectedShip = selectedShip;
	listener = NULL;
}

AsteroidsClient::~AsteroidsClient(void)
{
	Dir::remove(string(TEMPDIR));
	delete listener;
}

DWORD AsteroidsClient::run(void)
{
	start(ip, port, selectedShip);
	return 0;
}

void AsteroidsClient::sendStatus(string status)
{
	if (controller)
	{
		controller->updateClientStatus(status);
	}
}

void AsteroidsClient::start(string ip, int port, string selectedShip)
{
	//Se conecta al servidor y le envia el mensaje connected		
	// crea directorio temporal para guardar archivos de juego (images, xml)
	string filesDir(TEMPDIR);
	Dir::create(filesDir);	
	int sizeOfData = 0;
	try
	{
		sendStatus("Connecting to server...");

		client.doConnect(ip, port);

		isPlaying = true;

		sendStatus("Connected!");

		// envia la nave seleccionada
		client.doSend(selectedShip + ";");

		sendStatus("Waitting for players...");

		// recibir el paquete de inicio
		sizeOfData = client.doReceive();

		if (sizeOfData > 0)
			client.doSend("OK;");
		else
			client.doSend("BAD;");
	}
	catch (SocketException& se)
	{
		cout << se.getMessage() << endl;
		cout << "El codigo del error es: " << se.getErrorCode() << endl;
		sendStatus("Error connecting to server");
		return;
	}
	catch (...)
	{
		cout << "[AsteroidsClient] Unexpected error" << endl;
		sendStatus("Error connecting to server");
		return;		
	}
	auto_ptr<char> data(new char[sizeOfData]);
	client.doReceive(data.get(), sizeOfData);
	AsteroidsMsg msg;
	msg.setData(data.get(), sizeOfData);

	list<FileData> images = msg.getFilesData();
	list<FileData>::iterator it;
	for (it=images.begin(); it!=images.end(); it++)
	{
		cout << "copying " << it->filename << " --> " << filesDir + it->filename << endl;
		fstream imgFile(filesDir + (*it).filename, ios::binary | ios::out);
		imgFile.write(it->bytes.get(), it->len);
		imgFile.flush();
		imgFile.close();
	}

	// guarda el sceneFile
	sceneFileName = filesDir + "asteroids.xml";

	fstream sceneFile(sceneFileName, ios::out);
	sceneFile.write(msg.getSceneFile().c_str(), msg.getSceneFile().length());
	sceneFile.flush();
	sceneFile.close();	
	
	client.doSend("OK;");
	controller->startGame(sceneFileName);

	listener = new AsteroidsServerListener(&client, isPlaying, controller);
	Thread t(listener);
	t.start();
}

void AsteroidsClient::sendEvent(GameEvent::GameEventType eventType)//AsteroidsEvent e)
{
	AsteroidsEvent e(eventType);
	try
	{
		AsteroidsMsg clientEvent(AsteroidsMsg::CLIENT_UPDATE_MSG);
		clientEvent.setClientEvent(e.getType());
		client.doSend(clientEvent.toStringWithEnding());
		if (e.getType() == AsteroidsEvent::QUIT)
		{
			isPlaying = false;
			client.doClose();
		}
	}
	catch (SocketException&)
	{
		cout << "[AsteroidsClient] Error sending data to socket" << endl;
		controller->quitGame();	
	}
	catch (...)
	{
		cout << "[AsteroidsClient] Unexpected error" << endl;
		controller->quitGame();		
	}
}

void AsteroidsClient::quit(void)
{
}
