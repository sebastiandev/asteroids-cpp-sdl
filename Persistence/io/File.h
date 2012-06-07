#ifndef _FILE_H_
#define _FILE_H_

#include "IOException.h"
#include <list>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <Windows.h>

#undef DOMDocument

using namespace std;

namespace io
{
class File
{
public:
	File(void);
	File(string);
	virtual ~File(void);
	list<string> getFiles(void);// throws (IOException)
	void remove(void); // throws (IOException)
private:
	string toString(DWORD);
	wstring toWString(const string&);
	string name;
};
};

#endif
