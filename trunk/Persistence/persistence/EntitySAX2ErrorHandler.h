#ifndef _ENTITYSAX2ERRORHANDLER_H_
#define _ENTITYSAX2ERRORHANDLER_H_

#include "Logger.h"
#include <sstream>
#include <xercesc\sax\ErrorHandler.hpp>
#include <xercesc\sax\SAXParseException.hpp>

using namespace util;
using namespace std;
using namespace xercesc;

namespace persistence
{
class EntitySAX2ErrorHandler : public ErrorHandler
{
public:
	EntitySAX2ErrorHandler(string);
	virtual ~EntitySAX2ErrorHandler(void);
	virtual void warning(const SAXParseException&);
	virtual void error(const SAXParseException&);
	virtual void fatalError(const SAXParseException&);
	virtual void resetErrors(void);
private:
	string toString(int);
	string xmlFilename;
};
};

#endif
