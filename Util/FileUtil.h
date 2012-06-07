#ifndef _FILEUTIL_H_
#define _FILEUTIL_H_

#include <string>
#include <iostream>
#include <fstream>

namespace util
{
class FileUtil
{
	public:
	
    static unsigned long long getFileSize(std::string path);
    static unsigned long long getFileSize(char* path);
    static unsigned long long getFileSize(std::ifstream &file);

	static bool fileExists(std::string path);
	static bool fileExists(char* path);

	static void        fileToBytes (std::string path, char *&buffer, int &len);	
	static std::string fileToString(std::string path);

};
};

#endif //__FILEUTIL_H__
