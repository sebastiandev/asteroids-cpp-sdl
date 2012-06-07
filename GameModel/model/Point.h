#ifndef POINT_H
#define POINT_H

#include <sstream>

namespace model
{

class Point
{
public:
	Point() {}
	Point(double x, double y) : _x(x), _y(y) {}
	~Point(){}

	double x() const { return _x;}
	double y() const { return _y;}

	void setX(double x) { _x = x;}
	void setY(double y) { _y = y;}

	bool isValid() const { return (_x >= 0 && _y >= 0); }

	std::string toString() { std::stringstream ss; ss << "(" << _x << ", " << _y << ")"; return ss.str();}

protected:

	double _x, _y;
};
};
#endif