#ifndef _SDLSTATUSBAR_H_
#define _SDLSTATUSBAR_H_

#include "SDLLabel.h"

namespace sdl
{
class SDLStatusBar : public SDLComponent
{
public:
	SDLStatusBar(SDLSurface*);
	SDLStatusBar(int, SDLSurface*);
	virtual ~SDLStatusBar(void);
	virtual void draw(void);
	void setStatusText(string);
private:
	void initialize(void);
	SDLLabel* label;
};
};

#endif