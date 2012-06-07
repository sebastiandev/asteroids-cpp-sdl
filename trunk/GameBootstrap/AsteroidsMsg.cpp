#include "AsteroidsMsg.h"
#include "AsteroidsEventList.h"
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

AsteroidsMsg::AsteroidsMsg(int type)
{
	this->type = type;
	reset();
}


AsteroidsMsg::~AsteroidsMsg(void)
{
}

char* AsteroidsMsg::getData()
{
	char* buffer = NULL;
	
	if (type == SCENE_DATA_MSG)
	{
		int size = getLen();
		int offset = 0;

		buffer = new char[size];
		// primero guarda tipo de dato
		memcpy(buffer, &type, sizeof(type));
		offset += sizeof(type);
		// guarda tamaño de archivo xml
		int auxSize = sceneFile.size();
		memcpy(buffer+offset, &auxSize, sizeof(auxSize));

		int sizeOfFile = 0;
		memcpy((char*)&sizeOfFile, buffer+offset, sizeof(sizeOfFile));

		offset += sizeof(auxSize);
		
		// guarda archivo xml
		memcpy(buffer+offset, sceneFile.c_str(), auxSize);
		offset += auxSize;
		
		list<FileData>::iterator itData;
		for (itData=filesData.begin(); itData!=filesData.end();itData++)
		{
			FileData fd = (*itData);
			// copia tamaño de nombre
			auxSize = fd.filename.size();
			memcpy(buffer+offset, &auxSize, sizeof(auxSize));
			offset += sizeof(auxSize);
			// copia bytes de nombre de archivo
			memcpy(buffer+offset, fd.filename.c_str(), fd.filename.size());
			offset += fd.filename.size();
			
			// copia bytes de tamaño de archivo
			memcpy(buffer+offset, &(fd.len), sizeof(fd.len));
			offset += sizeof(fd.len);
			
			// copia bytes de archivo
			memcpy(buffer+offset, fd.bytes.get(), fd.len);			

			char *img = new char[fd.len];
			memcpy(img, buffer+offset, fd.len);

			offset += fd.len;			
		}
	}

	return buffer;
}

string AsteroidsMsg::toStringWithEnding()
{
	stringstream str;

	if (type == CLIENT_UPDATE_MSG)
	{
		////// Estructura del mensaje de update del cliente
		/// <MSGID><EVENTID><ControlCharacter>
		str << type;

		if (bulletCreated)
			str << AsteroidsEvent::SHOOT;
		else if (accelerating)
			str << AsteroidsEvent::ACCELERATE;
		else if (acceleratingLeft)
			str << AsteroidsEvent::ACCELERATE_LEFT;
		else if (acceleratingRight)
			str << AsteroidsEvent::ACCELERATE_RIGHT;
		else if (rotatingLeft)
			str << AsteroidsEvent::ROTATE_LEFT;
		else if (rotatingRight)
			str << AsteroidsEvent::ROTATE_RIGHT;
		else if (stopAccelerate)
			str << AsteroidsEvent::STOP_ACCELERATE;
		else if (stopRotation)
			str << AsteroidsEvent::STOP_ROTATION;
		else if (quit)
			str << AsteroidsEvent::QUIT;
	}
	else if (type == UPDATE_MSG)
	{
		////// Estructura del mensaje de update
		///        Asteroids data                   Ships data                           Bullets data                   End
		/// <MSGID>%A<ID>:<X>:<Y>|<ID>:<X>:<Y>| ....|%S<ID>:<X>:<Y>:<L|R|C>|<ID>:<X>:<Y>|%B<ID>:<X>:<Y>|<ID>:<X>:<Y>|...|<ControlCharacter>
		str << type;
		str << "%A";

		list<EntityData>::iterator it;
		for (it=asteroidsData.begin(); it!=asteroidsData.end(); it++)
		{
			str << (*it).id << ":" << (*it).x << ":" << (*it).y << "|";
		}
		str << "%S";
		for (it=shipsData.begin(); it!=shipsData.end(); it++)
		{
			str << (*it).id << ":" << (*it).x << ":" << (*it).y << ":" << (*it).rotation << ":" << (*it).acelerated  << "|";			
		}

		if (bulletsData.size() > 0)
		{
			str << "%B";
			map<int, EntityData>::iterator itMap;
			for (itMap=bulletsData.begin(); itMap!=bulletsData.end(); itMap++)
			{
				str << (*itMap).second.id << ":" << (*itMap).second.x << ":" << (*itMap).second.y << ":" << (*itMap).second.rotation << "|";
			}
		}

		if (bonusData.size() > 0)
		{
			str << "%X";
			map<int, EntityData>::iterator itMap;
			for (itMap=bonusData.begin(); itMap!=bonusData.end(); itMap++)
			{
				str << (*itMap).second.id << ":" << (*itMap).second.x << ":" << (*itMap).second.y <<  "|";
			}
		}
		
	}

	str << getControlCharacter();
	
	return str.str();
}

int AsteroidsMsg::getLen()
{
	int size = 0;

	if (type == SCENE_DATA_MSG)
	{
		size = sizeof(int);//tamaño delindicador de tipo
		size += sizeof(sceneFile.size()) + sceneFile.size();// bytes para el tamaño y tamaño del archivo xml

		list<FileData>::iterator itData;
		for (itData=filesData.begin(); itData!=filesData.end();itData++)
		{
			FileData fd = (*itData);
			size += sizeof(fd.filename.size()) + fd.filename.size();//indicador del tamaño de nombre del archivo + tamaño del nombre
			size += sizeof(fd.len)+ fd.len;//indicador del tamaño de bytes del archivo + tamaño del archivo
		}
	}

	return size;
}

void AsteroidsMsg::setData(char* data, int len)
{
	if (len <= sizeof(type))
		return;

	int offset = 0;
	memcpy((char*)&type, data+offset, sizeof(type));
	//cout << "Got: " << type << " data" << endl;

	if (type == SCENE_DATA_MSG)
	{
		offset += sizeof(type);
		int sizeOfFile = 0;
		memcpy((char*)&sizeOfFile, data+offset, sizeof(sizeOfFile));
		offset += sizeof(int);
		//cout << "Xml File has " << sizeOfFile << " bytes" << endl;

		char *xmlfile = new char[sizeOfFile];
		memcpy(xmlfile, data + offset, sizeOfFile);
		//cout << "Xml File: '" << string(xmlfile, sizeOfFile) << "'" << endl;
		offset += sizeOfFile;

		// guarda el Scenefile
		this->sceneFile = string(xmlfile, sizeOfFile);

		// carga archivos de imagnes
		int size;
		char *nombre, *img;
		while (offset < len)
		{
			// carga tamaño nombre de archivo
			memcpy((char*)&size, data+offset, sizeof(size));
			offset += sizeof(size);
			
			// carga nombre archivo
			nombre = new char[size];
			memcpy(nombre, data+offset, size);
			string imageName(nombre, size);
			//cout << "got file '" << imageName << "'" << endl;
			offset += size;

			// carga tamaño archivo
			memcpy((char*)&size, data+offset, sizeof(size));
			offset += sizeof(size);
			// carga archivo
			img = new char[size];
			memcpy(img, data+offset, size);
			offset += size;

			FileData aux;
			aux.len = size;
			aux.bytes.reset(new char[size]);
			memcpy(aux.bytes.get(), img, size);
			aux.filename = imageName;
			
			// agrega el archivo a la lista
			this->filesData.push_back(aux);

			delete[] nombre;
			delete[] img;
		}
	}
}

void AsteroidsMsg::setData(string data)
{
	stringstream strtype;
	strtype << data.substr(0, 1);
	strtype >> type;

	if (type == CLIENT_UPDATE_MSG)
	{
		int eventCode;
		strtype.clear();

		strtype << data.at(1);
		strtype >> eventCode;
		clientEvent = eventCode;

		switch (eventCode)
		{
		case AsteroidsEvent::ACCELERATE:       accelerating = true;
					break;
		case AsteroidsEvent::ACCELERATE_LEFT:  acceleratingLeft = true;
					break;
		case AsteroidsEvent::ACCELERATE_RIGHT: acceleratingRight = true;
					break;
		case AsteroidsEvent::ROTATE_LEFT:      rotatingLeft = true;
					break;
		case AsteroidsEvent::ROTATE_RIGHT:     rotatingRight = true;
					break;
		case AsteroidsEvent::SHOOT:            bulletCreated = true;
					break;
		case AsteroidsEvent::STOP_ACCELERATE:  stopAccelerate = true;
					break;
		case AsteroidsEvent::STOP_ROTATION:    stopRotation = true;
					break;
		case AsteroidsEvent::QUIT:             quit = true;
					break;
		}
	}
	else if (type == UPDATE_MSG)
	{
		size_t asteroidsIdx   = data.find("%A");	
		size_t shipsIdx       = data.find("%S");
		size_t bulletsIdx     = data.find("%B");
		size_t bonusIdx       = data.find("%X");		
		size_t endIdx         = data.size();
		size_t endForShipIdx  = string::npos;
		size_t endForBulletsIdx = string::npos;

		if (asteroidsIdx != string::npos && shipsIdx != string::npos)
		{
			//cout << "llamo asteroids " << asteroidsIdx << endl;
			list<EntityData> asteroids = getEntitiesFromUpdateMsg(data, asteroidsIdx+2, shipsIdx);
			asteroidsData.insert(asteroidsData.begin(), asteroids.begin(), asteroids.end());
		}

		if(bulletsIdx != string::npos)
			endForShipIdx = bulletsIdx;
		else if(bonusIdx != string::npos)
			endForShipIdx = bonusIdx;
		else
			endForShipIdx = endIdx;

		if(bonusIdx != string::npos)
			endForBulletsIdx = bonusIdx;
		else
			endForBulletsIdx = endIdx;

		if (bulletsIdx != string::npos && endForBulletsIdx != string::npos)
		{	
 			list<EntityData> bullets = getEntitiesFromUpdateMsg(data, bulletsIdx+2, endForBulletsIdx);
			
			list<EntityData>::iterator it;
			for (it=bullets.begin(); it!=bullets.end(); it++)
				bulletsData.insert(pair<int, EntityData>(it->id, *it));
		}
		
		if (shipsIdx != string::npos && endForShipIdx != string::npos)
		{
			//cout << "llamo ships solo" << shipsIdx << endl;
			list<EntityData> ships = getEntitiesFromUpdateMsg(data, shipsIdx+2, endForShipIdx);
			shipsData.insert(shipsData.begin(), ships.begin(), ships.end());
		}

		if (bonusIdx != string::npos)
		{
			list<EntityData> bonuses = getEntitiesFromUpdateMsg(data, bonusIdx+2, endIdx);

			list<EntityData>::iterator it;
			for (it=bonuses.begin(); it!=bonuses.end(); it++)
				bonusData.insert(pair<int, EntityData>(it->id, *it));			
			//cout << "llego un bonus: " << bonusIdx << "msg: " << data << endl;
		}
	}
}

list<string> split(const string& strValue, char separator)
{
    list<string> listResult;
    int startpos=0;
    int endpos=0;

    endpos = strValue.find_first_of(separator, startpos);
    while (endpos != -1)
    {       
        listResult.push_back(strValue.substr(startpos, endpos-startpos)); 
        startpos = endpos+1; 
        endpos = strValue.find_first_of(separator, startpos);
        if(endpos==-1)
            listResult.push_back(strValue.substr(startpos));
    }
    return listResult;
}


list<EntityData> AsteroidsMsg::getEntitiesFromUpdateMsg(string data, size_t begin, size_t end)
{
	list<EntityData> entities;
	int id;
	double x, y, rotation = 0.0;
	int acelerated = 0;
	//cout << "Cadena completa: " << data << endl;
	//cout << "A evaluar: " << data.substr(begin,end-begin) << endl;

	list<string> tokens = split(data.substr(begin,end-begin),'|');
	list<string>::iterator it;
	for (it=tokens.begin();it!=tokens.end(); it++)
	{
		id = 0; x = 0; y = 0; rotation = 0; acelerated = 0;
		//cout << "Token: " << *it << endl;
		list<string> subToken = split(*it,':');
		list<string>::iterator it2;
		int counter = 1;
		for (it2=subToken.begin();it2!=subToken.end(); it2++)
		{				
			switch (counter)
			{
				case 1: id = atoi((*it2).c_str());
					break;
				case 2:	x = strtod((*it2).c_str(),NULL);
					break;
				case 3: y = strtod((*it2).c_str(),NULL);
					break;
				case 4:	rotation = strtod((*it2).c_str(),NULL);
					break;
				case 5:	acelerated = atoi((*it2).c_str());
					break;
			}
			counter++;
		}	
		
		if (counter > 1)
		{
			//cout << "Entity: " << id << " -> " << x << ", " <<  y << ", " << rotation << "," << acelerated << endl;
			EntityData e(id, x, y);
			e.rotation = rotation;
			e.acelerated = acelerated;
			entities.push_back(e);
		}

	}	

	return entities;
}

void AsteroidsMsg::addFileData(std::string name, char* bytes, unsigned long long len)
{
	FileData file;
	file.filename = name;
	file.len = (int)len; 
	file.bytes.reset(new char[(int)len]);
	memcpy(file.bytes.get(), bytes, (int)len);
	
	filesData.push_back(file);	
}
void AsteroidsMsg::addAsteroidPosition(int asteroidId, double x, double y)
{
	EntityData e(asteroidId, x, y);
	asteroidsData.push_back(e);
}
void AsteroidsMsg::addShipPosition(int shipId, double x, double y, double rotation, int acelerated)
{
	EntityData e(shipId, x, y);

	if (rotation < 0)
		rotation = rotation + 360;
	e.rotation = rotation;
	e.acelerated = acelerated;
	shipsData.push_back(e);
}

void AsteroidsMsg::addBulletPosition(int bulletId, double x, double y, double rotation)
{
	EntityData e(bulletId, x, y);
	e.rotation = rotation;
	bulletsData.insert(pair<int, EntityData>(bulletId, e));
}

void AsteroidsMsg::addBonusPosition(int bonusId, double x, double y)
{
	EntityData e(bonusId, x, y);
	bonusData.insert(pair<int, EntityData>(bonusId, e));;
}

void AsteroidsMsg::setClientEvent(int type)
{
	switch (type)
	{
		case AsteroidsEvent::ACCELERATE:       accelerating = true;
					break;
		case AsteroidsEvent::ACCELERATE_LEFT:  acceleratingLeft = true;
					break;
		case AsteroidsEvent::ACCELERATE_RIGHT: acceleratingRight = true;
					break;
		case AsteroidsEvent::ROTATE_LEFT:      rotatingLeft = true;
					break;
		case AsteroidsEvent::ROTATE_RIGHT:     rotatingRight = true;
					break;
		case AsteroidsEvent::SHOOT:            bulletCreated = true;
					break;
		case AsteroidsEvent::STOP_ACCELERATE:  stopAccelerate = true;
					break;
		case AsteroidsEvent::STOP_ROTATION:    stopRotation = true;
					break;
		case AsteroidsEvent::QUIT:             quit = true;
					break;
	}
}
void AsteroidsMsg::setClientId(int id)
{
	clientId = id;
}


void AsteroidsMsg::reset()
{
	filesData.clear();
	asteroidsData.clear();
	shipsData.clear();
	bulletsData.clear();
	bonusData.clear();

	bulletCreated     = false;
	accelerating      = false;
	acceleratingLeft  = false; 
	acceleratingRight = false; 
	rotatingLeft      = false; 
	rotatingRight     = false; 
	quit              = false;
	stopAccelerate    = false;
	stopRotation      = false;
}