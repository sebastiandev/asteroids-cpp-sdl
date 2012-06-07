#ifndef _UTILS_H_
#define _UTILS_H_

#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

namespace util
{
	class Utils
	{
	public:

		struct delete_object
		{
			template<typename T> void operator()(T *p){ delete p;}
		};

		inline static bool fileExists(string filepath)
		{
			ifstream aux(filepath);
			return aux.is_open();
		}
		
		inline static string timeStamp()
		{
			# define TIME_SIZE 40
			std::time_t now = std::time(NULL);
			const struct std::tm * tm_ptr = std::localtime(&now);
			char *s = new char[TIME_SIZE];

			size_t len = std::strftime(s, TIME_SIZE, "%Y/%m/%d %X ", tm_ptr);
			return string(s);
			# undef TIME_SIZE
		}
		
	};

};

#endif