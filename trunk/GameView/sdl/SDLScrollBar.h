#ifndef _SDLSCROLLBAR_H_
#define _SDLSCROLLBAR_H_

#include "SDLComponent.h"
#include "SDL_gfxPrimitives.h"
#include <string>

using namespace std;

namespace sdl
{
class SDLScrollBar : public SDLComponent
{
public:
	SDLScrollBar(SDLSurface*);
	virtual ~SDLScrollBar(void);
	void setUnitIncrement(int);
	void setMaximumIncrement(int);
	int getMaximumIncrement(void);
	int getIncrement(void);
	virtual void processEvent(SDLEvent*);
	virtual void draw(void);
private:
	void scrollUp(void);
	void scrollDown(void);
	int unitIncrement;
	int maximumIncrement;
	int increment;
};
};

#endif
