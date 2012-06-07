#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "Attribute.h"
#include "ElementLocation.h"
#include <string>
#include <list>

using namespace std;

namespace persistence
{
class Element
{
public:
	Element(string);
	virtual ~Element(void);
	string getName(void);
	void addAttributes(list<Attribute*>);
	list<Attribute*> getAttributes(void);
	void setLocation(ElementLocation*);
	ElementLocation* getLocation(void);
private:
	string name;
	list<Attribute*> attributes;
	ElementLocation* location;
};
};

#endif
