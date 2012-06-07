#ifndef _IOEXCEPTION_H_
#define _IOEXCEPTION_H_

#pragma once
#include <string>

using namespace std;

namespace io
{
class IOException
{
public:
	IOException(string);
	virtual ~IOException(void);
	string getMessage(void) const;
private:
	string message;
};
};

#endif
