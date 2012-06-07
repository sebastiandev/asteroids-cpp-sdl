#include "ClientHandler.h"
#include "AsteroidsMsg.h"
#include "..\Util\FileUtil.h"
#include "net\SocketException.h"

#include <sstream>
#include <stdio.h>


using namespace net;
using namespace model;
using namespace std;
using namespace util;

ClientHandler::ClientHandler(TCPSocket *cliente, int id, AsteroidsEventList *eventQueue)
{
	this->id         = id;
	stringstream ss;
	ss << id;
	ss >> clientId;

	this->cliente    = cliente;
	this->eventQueue = eventQueue;

	clientStatus       = IDLE;
}


ClientHandler::~ClientHandler(void)
{
}

DWORD ClientHandler::run(void)
{
	char *bytes = NULL;
	int bytesLen = 0;

	clientStatus = INITIALIZING_CLIENT;

	///////// arma el mensaje con el archivo xml y las imagenes necesarias
	AsteroidsMsg msg(AsteroidsMsg::SCENE_DATA_MSG);
	msg.addSceneFile(sceneFile);
	
	// carga todas las imagenes
	list<string>::iterator it;
	for(it=images.begin();it!=images.end(); it++)
	{
		string filename = (*it);
		//cout << "loading file to send: " << filename << endl;
		filename = filename.erase(0, filesDir.size()+1);

		delete[] bytes;
		FileUtil::fileToBytes((*it), bytes, bytesLen);

		msg.addFileData(filename, bytes, (int)bytesLen);
	}

	delete[] bytes;

	cliente->doSend(msg.getLen());
	string response = cliente->doReceive(";");
	if (response.compare("OK") != 0)
	{
		error = 1;
	}
	
	cliente->doSend(msg.getData(), msg.getLen());

	response = cliente->doReceive(";");
	if (response.compare("OK") != 0)
	{
		error = 1;
	}

	clientStatus = WAITING_TO_START;
	while (clientStatus == WAITING_TO_START)
	{
	}
	
	readyForNextUpdate = true;

	while (clientStatus == LISTENING_TO_CLIENT)
	{
		try
		{
			msg.reset();
			string clientUpdate = cliente->doReceive(AsteroidsMsg::getControlCharacter());

			processClientMsg(clientUpdate);
		}
		catch (SocketException&)
		{
			cout << "[ClientHandler] Socket disconnected" << endl;
			clientStatus = DISCONNECTED;
			return 0;
		}
		catch (...)
		{
			cout << "[ClientHandler] Unexpected error" << endl;
			clientStatus = DISCONNECTED;
			return 0;
		}
	}

	try
	{
		cliente->doClose();
	}
	catch (...)
	{
	}

	return 0;
}

void ClientHandler::processClientMsg(string clientUpdate)
{
	size_t nextMsgBegin = 0;
	size_t nextMsgEnd   = 0;
	
	AsteroidsMsg asteroidsMsg(AsteroidsMsg::SCENE_DATA_MSG);

	while (nextMsgBegin <= clientUpdate.size() && nextMsgBegin != string::npos)
	{
		nextMsgEnd = clientUpdate.find_first_of(";", nextMsgBegin);
		if (nextMsgEnd == string::npos)
			nextMsgEnd = clientUpdate.size();

		string msg( clientUpdate.substr(nextMsgBegin, nextMsgEnd - nextMsgBegin) );
		if (msg.compare("OK") == 0)
		{
			readyForNextUpdate = true;
		}
		else
		{
			// agregar evento en la lista de eventos del servidor (clienteId - Evento)
			asteroidsMsg.setData(msg);
			eventQueue->addEvent(AsteroidsEvent(asteroidsMsg.getClientEvent(), id));
		}

		nextMsgBegin = nextMsgEnd + 1;
	}
}

void ClientHandler::sendUpdate(AsteroidsMsg &update)
{
	try
	{
		cliente->doSend(update.toStringWithEnding());
		readyForNextUpdate = false;
	}
	catch (SocketException&)
	{
		clientStatus = DISCONNECTED;
		cout << "[ClientHandler] Send update failed: Socket not avaliable." << endl;
	}
	catch (...)
	{
		clientStatus = DISCONNECTED;
		cout << "[ClientHandler] Send update failed: Unexpected error" << endl;
	}
}

void ClientHandler::sendQuit()
{
	try
	{
		cliente->doSend("QUIT" + AsteroidsMsg::getControlCharacter());
		clientStatus = IDLE;
		cliente->doClose();
	}
	catch (SocketException&)
	{
		clientStatus = DISCONNECTED;
	}
	catch (...)
	{
		clientStatus = DISCONNECTED;
	}
}


void ClientHandler::stop()
{
	clientStatus = IDLE;
}