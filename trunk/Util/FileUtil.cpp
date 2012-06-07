#include "FileUtil.h"
#include <sys/stat.h>
#include <string>
#include <vector>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;
using namespace util;

unsigned long long FileUtil::getFileSize(string path)
{
	struct stat filestatus;
	stat(path.c_str(), &filestatus);
	
	return filestatus.st_size;		
}

unsigned long long FileUtil::getFileSize(char* path)
{
	return getFileSize(string(path, strlen(path)));
}

unsigned long long FileUtil::getFileSize(ifstream &file)
{
    unsigned long long position = file.tellg();
	file.seekg (0, ios::end);
    unsigned long long size = file.tellg();
	file.seekg (position);
	
	return size;
}

bool FileUtil::fileExists(string path)
{
	struct stat stFileInfo;
	bool blnReturn; 
	int intStat; 

	// Attempt to get the file attributes 
	intStat = stat(path.c_str(),&stFileInfo); 
	if(intStat == 0) 
	{ 
    // We were able to get the file attributes 
    // so the file obviously exists. 
		blnReturn = true; 
	} 
	else
	{ 
		// We were not able to get the file attributes. 
		// This may mean that we don't have permission to 
		// access the folder which contains this file.
		blnReturn = false; 
	} 
	
	return(blnReturn); 
}

bool FileUtil::fileExists(char* path)
{
	return fileExists(string(path, strlen(path)));
}

void FileUtil::fileToBytes(std::string path, char *&buffer, int &len)
{
	ifstream file (path, ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{		
		len = (int) file.tellg();
		buffer = new char [len];
		file.seekg (0, ios::beg);
		file.read (buffer, len);
		file.close();
	}
}

string FileUtil::fileToString(std::string path)
{
	FILE* pFile = (FILE*) NULL; 
	pFile = fopen((char*) path.c_str() , "r");
	char buffer [100];
	std::string filestr;
	while (!feof(pFile))
	{
		if ( fgets (buffer , 100 , pFile) != NULL )
			filestr.append(buffer);			
	}

	fclose (pFile);
	return filestr;
}