#ifndef _SCENEREPOSITORY_H_
#define _SCENEREPOSITORY_H_

#include "..\io\File.h"
#include <string>
#include <list>

using namespace io;
using namespace std;

const string CONFIG_SERVER_DIRECTORY = "../config/server";

namespace persistence
{
class SceneRepository
{
public:
	SceneRepository(string);
	virtual ~SceneRepository(void);
	list<string> getSceneNames(void);
private:
	File* directory;
};
};

#endif
