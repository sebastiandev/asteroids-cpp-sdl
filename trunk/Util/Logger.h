#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <fstream>
#include <string>

using namespace std;

namespace util
{
	class Logger
	{
	public:

		typedef enum logLevel{LDEBUG=0, LINFO, LERROR};
		
		~Logger();

		static Logger& instance();

		void log(string msg, int level=LDEBUG, bool timestamp=true);
		
	private:
		Logger();

		ofstream file;
	};
};

#endif