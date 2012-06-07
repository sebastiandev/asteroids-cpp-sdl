#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "TCPSocket.h"
#include "SocketException.h"

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
using namespace net;

TCPSocket::TCPSocket()
{
	WSADATA wsaData;
	int res;
	res = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (res != 0)
	{
		throw SocketException("Couldnt start socket library");
	}
	this->descriptor = socket(AF_INET , SOCK_STREAM , 0);
	if (descriptor == INVALID_SOCKET)
	{
		throw SocketException("Error creating socket");	
	}
	cout << "socket created" << endl;
	this->creado = true;
}

TCPSocket::~TCPSocket() 
{
	if (this->creado)
	{
		this->doClose();
	}
	WSACleanup();
}

void TCPSocket::doBind(int puerto)
{
	sockaddr_in direccion_server;
	memset((char*)&(direccion_server), 0, sizeof(direccion_server));
	direccion_server.sin_family = AF_INET;
	direccion_server.sin_port = htons(puerto);
	direccion_server.sin_addr.s_addr = INADDR_ANY;
	
	if (bind(this->descriptor, (struct sockaddr*)&direccion_server, (socklen_t)sizeof(sockaddr)) < 0)
	{
		throw SocketException("Error binding socket");
	}
	cout << "socket binded" << endl;
}

void TCPSocket::doListen(int max_cola_conexiones)
{
	if (listen(this->descriptor, max_cola_conexiones) == SOCKET_ERROR)
	{
		throw SocketException("Error listening on socket");	
	}
	cout << "socket listening..." << endl;
}

void TCPSocket::doConnect(const string& ip, int puerto) 
{
	sockaddr_in direccion_server;
	memset((char*)&(direccion_server), 0, sizeof(direccion_server));
	direccion_server.sin_family = AF_INET;
	direccion_server.sin_port = htons(puerto);
	direccion_server.sin_addr.s_addr = inet_addr(ip.c_str());

	if (connect (this->descriptor, (struct sockaddr*)&direccion_server, sizeof(direccion_server)) == SOCKET_ERROR)
	{
		throw SocketException("Error al intentar conectar el socket", WSAGetLastError());	
	}
	cout << "socket connected" << endl;
}

void TCPSocket::doShutDown() 
{
	shutdown(this->descriptor, SD_BOTH);
}

void TCPSocket::doClose() 
{
	closesocket(this->descriptor);
	this->creado = false;
}

TCPSocket* TCPSocket::doAccept() 
{
	socklen_t tamanio = sizeof(struct sockaddr_in);
	int nuevo_cliente_descriptor;
	sockaddr_in dir_cliente;
	if ((nuevo_cliente_descriptor = accept(this->descriptor, (struct sockaddr *)&dir_cliente, &tamanio)) == INVALID_SOCKET)
	{
		throw SocketException("Error accepting new socket coonection");	
	}
	TCPSocket* sock_cliente_nuevo = new TCPSocket;
	sock_cliente_nuevo->descriptor = nuevo_cliente_descriptor;
	sock_cliente_nuevo->creado = true;

	cout << "Client accepted" << endl;
	return sock_cliente_nuevo;
}

void TCPSocket::doReceive(char* data, int longitud)
{
	int total_recibido = 0;
	while (total_recibido < longitud) 
	{
		int cantidad = recv(this->descriptor, data+total_recibido, longitud-total_recibido, 0);
		if (cantidad == 0)
		{
			continue;
		}
		else if (cantidad == SOCKET_ERROR)
		{
			throw SocketException("Error retrieving data from socket");
		}
		total_recibido += cantidad;
	}
}

void TCPSocket::doReceive(char* &data, string controlchar)
{
	char buffer[MAX_BUFFER_READ];
	memset(&buffer, 0, MAX_BUFFER_READ);
	string tempData;
	bool controlFound = false;
	while (!controlFound) 
	{
		int len = recv(this->descriptor, buffer, MAX_BUFFER_READ, 0);
		if (len == SOCKET_ERROR)
		{
			throw SocketException("Error retrieving data from socket");
		}
		tempData.append(buffer,0,MAX_BUFFER_READ);
		size_t index = tempData.find_last_of(controlchar);
		if (index != string::npos)
		{
			controlFound = true;
			tempData = tempData.substr(0, index);
			data = new char[tempData.size() + 1];
			memset(data, 0, tempData.size() + 1);
			memcpy(data, tempData.c_str(), tempData.size());
		}
	}
}

string TCPSocket::doReceive(string controlchar)
{
	char *data;
	doReceive(data, controlchar);
	string buff(data);
	delete[] data;
	return buff;
}

int TCPSocket::doReceive()
{
	char data[4];
	int number;
	int total_recibido = 0;
	while (total_recibido < 4) 
	{
		int cantidad = recv(this->descriptor, data+total_recibido, 4-total_recibido, 0);
		if (cantidad == 0)
		{
			continue;
		}
		else if (cantidad == SOCKET_ERROR)
		{
			throw SocketException("Error retrieving data from socket");
		}
		total_recibido += cantidad;
	}
	memcpy(&number, data, sizeof(int));
	return number;
}

void TCPSocket::doSend(char* data, int longitud) 
{
	int total_enviado = 0;
	while (total_enviado < longitud)
	{
		int cantidad = send(this->descriptor, data+total_enviado, longitud-total_enviado, 0);
		if (cantidad <= 0)
		{
			throw SocketException("Error sending data to socket");
		}
		total_enviado += cantidad;
	}
}

void TCPSocket::doSend(string buffer) 
{
	int total_enviado = 0;
	while ((unsigned int)total_enviado < buffer.length())
	{
		int cantidad = send(this->descriptor, buffer.c_str()+total_enviado, buffer.length()-total_enviado, 0);
		if (cantidad == SOCKET_ERROR || cantidad < 0)
		{
			throw SocketException("Error sending data to socket");
		}
		total_enviado += cantidad;
	}
}

void TCPSocket::doSend(int number)
{
	char buffer[4];
	memcpy(buffer, &number, sizeof(number));
	int total_enviado = 0;
	while (total_enviado < 4)
	{
		int cantidad = send(this->descriptor, buffer+total_enviado, sizeof(number)-total_enviado, 0);
		if (cantidad == SOCKET_ERROR || cantidad < 0)
		{
			throw SocketException("Error sending data to socket");
		}
		total_enviado += cantidad;
	}
}
