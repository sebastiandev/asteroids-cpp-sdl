#ifndef _ASTEROIDSMSG_H_
#define _ASTEROIDSMSG_H_

#include <string>
#include <list>
#include <map>
#include <memory>

class EntityData
{
public:
	EntityData(int id, double x, double y) { this->id = id; this->x = x; this->y = y; rotation = 0; acelerated = 0;}
	EntityData(const EntityData &e)        {  this->id = e.id; this->x = e.x; this->y = e.y; rotation = e.rotation; acelerated = e.acelerated;}
	EntityData()                           { id = 0; x = 0; y = 0; rotation = 0; acelerated = 0;}

	int id;
	double x, y, rotation;
	int acelerated;
};

class FileData
{
public:
	FileData(){}
	FileData(const FileData &fd)
	{
		filename = fd.filename;
		len = fd.len;
		bytes.reset(new char[len]);
		memcpy(bytes.get(), fd.bytes.get(), len);
	}

	std::string filename;
	std::auto_ptr<char> bytes;
	int len;
};

class AsteroidsMsg
{
public:
	typedef enum type { LOGIN_MSG, SCENE_DATA_MSG, START_MSG, UPDATE_MSG, CLIENT_UPDATE_MSG};

	AsteroidsMsg(int type);
	AsteroidsMsg(){}
	~AsteroidsMsg(void);

	// getters
	char* getData();
	int   getLen ();

	static std::string getControlCharacter() { return ";";}

	int         getType     () { return type;}
	std::string getLoginMsg () { return loginMsg;}
	std::string getStartMsg () { return startMsg;}

	std::string getSceneFile() { return sceneFile;}

	std::list<FileData>   getFilesData    () { return filesData;}
	std::list<EntityData> getAsteroidsData() { return asteroidsData;}
	std::list<EntityData> getShipsData    () { return shipsData;}
	std::map<int, EntityData> getBulletsData  () { return bulletsData;}
	std::map<int, EntityData> getBonusData  () { return bonusData;}

	int getClientId   () { return clientId;}
	int getClientEvent() { return clientEvent;}

	// setters
	void setData(char* data, int len);
	void setData(std::string data);

	void setType    (int type)        { this->type = type;}
	void setLoginMsg(std::string msg) { this->loginMsg = msg;}
	void setStartMsg(std::string msg) { this->startMsg = msg;}

	void addSceneFile       (std::string sceneFile) { this->sceneFile = sceneFile;}

	void addFileData        (std::string name, char* bytes, unsigned long long len);
	void addAsteroidPosition(int asteroidId, double x, double y);
	void addShipPosition    (int shipId, double x, double y, double rotation, int acelerated);
	void addBulletPosition  (int bulletId, double x, double y, double rotation);
	void addBonusPosition(int bonusId, double x, double y);

	void reset();

	void setClientEvent(int type);
	void setClientId   (int id);

	bool isStopAcceleration     () { return stopAccelerate;}
	bool isStopRotation         () { return stopRotation;}

	bool isNewBullet            () { return bulletCreated;}
	bool isShipAccelerating     () { return accelerating;}
	bool isShipAcceleratingLeft () { return acceleratingLeft;}
	bool isShipAcceleratingRight() { return acceleratingRight;}
	bool isShipRotatingLeft     () { return rotatingLeft;}	
	bool isShipRotatingRight    () { return rotatingRight;}
	bool hasClientQuit          () { return quit;}

	std::string toStringWithEnding();

private:

	std::list<EntityData> getEntitiesFromUpdateMsg(std::string data, std::size_t begin, std::size_t end);

	std::list<FileData> filesData;
	std::list<EntityData> asteroidsData, shipsData;
	std::map<int, EntityData> bulletsData;
	std::map<int, EntityData> bonusData;

	std::string loginMsg, startMsg, sceneFile, updateMsg;
	int type, clientId, clientEvent;

	bool bulletCreated, accelerating, acceleratingLeft, acceleratingRight, rotatingLeft, rotatingRight, quit, stopAccelerate, stopRotation;
};

#endif