#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

#include "Dimension.h"

namespace sdl
{
class Viewport : public Dimension
{
public:
	Viewport(void);
	Viewport(int, int, int, int);
	virtual ~Viewport(void);
	void setX(int);
	void setY(int);
	void setWidth(int);
	void setHeight(int);
};
};

#endif
