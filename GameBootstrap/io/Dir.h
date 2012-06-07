#ifndef _DIR_H_
#define _DIR_H_

#include "io\File.h"
#include "io\IOException.h"
#include <windows.h>
#include <tchar.h> 
#include <stdio.h>
#include <strsafe.h>
#include <iostream>
#include <string>
#include <list>

using namespace std;

namespace io
{
class Dir
{
public:
	Dir(string path);
	Dir(){}
	~Dir();
	static bool create(string path);
	static list<string> getFiles(string dirpath, list<string> filter, bool recursive=true);
	static list<string> getFilesWithoutPath(string dirpath, list<string> filter, bool recursive=true);
	static bool remove(string dirPath, bool subdirsAndFiles=true);
	static bool removeFile(string filePath);
private:
	string path;
};
};

#endif
