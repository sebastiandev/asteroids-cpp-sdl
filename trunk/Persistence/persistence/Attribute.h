#ifndef _ATTRIBUTE_H_
#define _ATTRIBUTE_H_

#include "ElementLocation.h"
#include <string>

using namespace std;

namespace persistence
{
class Attribute
{
public:
	Attribute(string, string);
	virtual ~Attribute(void);
	string getName(void) const;
	void setValue(string);
	string getValue(void) const;
	void setLocation(ElementLocation*);
	ElementLocation* getLocation(void);
private:
	string name;
	string value;
	ElementLocation* location;
};
};

#endif
