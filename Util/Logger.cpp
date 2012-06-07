#include "Logger.h"
#include "Utils.h"
using namespace util;

Logger::Logger()
{
   file.open ("asteroid.log", std::ios::out | std::ios::app);
}

Logger::~Logger()
{
	file.close();
}
Logger& Logger::instance()
{
	static Logger instance;
	return instance;
}

void Logger::log(string msg, int level, bool timestamp)
{
	string line;

	if (timestamp)
		line.append(Utils::timeStamp());

	if (level == LDEBUG)
		line.append("[Debug] ");
	else if (level == LINFO)
		line.append("[Info ] ");
	else
		line.append("[Error] ");
	
	line.append(msg);

	file << line << std::endl; 
}



