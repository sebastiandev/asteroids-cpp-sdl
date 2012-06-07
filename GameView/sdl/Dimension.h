#ifndef _DIMENSION_H_
#define _DIMENSION_H_

namespace sdl
{
class Dimension
{
public:
	Dimension(int, int, int, int);
	virtual ~Dimension(void);
	int getX(void);
	int getY(void);
	int getWidth(void);
	int getHeight(void);
	Dimension* intersect(Dimension*);
protected:
	Dimension(void);
	int x;
	int y;
	int width;
	int height;
};
};

#endif
