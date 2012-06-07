#ifndef POLYGON_H
#define POLYGON_H

#include "Point.h"
#include <vector>

namespace model
{
class Polygon
{
public:

	Polygon(void);
	Polygon(std::vector<Point> &vertices);

	virtual ~Polygon(void);

	std::vector<Point*> getVertices();
	void  setVertices(std::vector<Point> &vertices);
		
	void  addVertex(Point p);

	Point calculateCenter() const;
	int   maxWidth () const;
	int   maxHeight() const;

	void  setRotatingPoint(Point point);

	void  rotate(double angle);
	void  expand(double ratio);
	void  expand(double xRatio, double yRatio);

	bool  containsPoint(const Point &p) const;

private:

	void doExpand(double xRatio, double yRatio);

	std::vector<Point*> vertices;
	Point rotatingPoint;
	int   width, height;
	
};
};
#endif
