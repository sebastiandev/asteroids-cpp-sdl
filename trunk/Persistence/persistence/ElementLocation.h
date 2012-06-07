#ifndef _ELEMENTLOCATION_H_
#define _ELEMENTLOCATION_H_

namespace persistence
{
class ElementLocation
{
public:
	ElementLocation(int, int);
	virtual ~ElementLocation(void);
	int getLineNumber(void);
	int getColumnNumber(void);
private:
	int xmlLineNumber;
	int xmlColumnNumber;
};
};

#endif
