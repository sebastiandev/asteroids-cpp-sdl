#ifndef _PERSISTENCEEXCEPTION_H_
#define _PERSISTENCEEXCEPTION_H_

#include <string>

using namespace std;

namespace persistence
{
class PersistenceException
{
public:
	PersistenceException(string, string="", int=0, int=0);
	virtual ~PersistenceException(void);
	string getMessage(void) const;
	string getConfigFile(void) const;
	int getLineError(void) const;
	int getColumnError(void) const;
private:
	string message;
	string file;
	int line;
	int column;
};
};

#endif
