#include "SceneRepository.h"

using namespace persistence;

SceneRepository::SceneRepository(string directoryPath)
{
	directory = new File(directoryPath);
}

SceneRepository::~SceneRepository(void)
{
	delete directory;
}

list<string> SceneRepository::getSceneNames(void)
{
	string extension = ".xml";
	list<string> names;
	list<string> filenames = directory->getFiles();
	list<string>::iterator it;
	for (it=filenames.begin(); it!=filenames.end(); it++)
	{
		size_t nameIndex = (*it).find(extension);
		if (nameIndex!=string::npos && nameIndex+extension.size()==(*it).size())
		{
			names.push_back((*it).substr(0, nameIndex));
		}
	}
	return names;
}
