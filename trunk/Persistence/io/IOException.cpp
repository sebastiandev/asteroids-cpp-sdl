#include "IOException.h"

using namespace io;

IOException::IOException(string msg) : message(msg)
{
}

IOException::~IOException(void)
{
}

string IOException::getMessage(void) const
{
	return message;
}

