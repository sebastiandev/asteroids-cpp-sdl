#ifndef _SDLTOGGLEBUTTON_H_
#define _SDLTOGGLEBUTTON_H_

#include "SDLButton.h"

namespace sdl
{
class SDLToggleButton : public SDLButton
{
public:
	SDLToggleButton(int, int, int, int, string, SDLSurface*);
	virtual ~SDLToggleButton(void);
	virtual void processEvent(SDLEvent*);
protected:
	virtual void drawBorder(void);
	virtual void drawBackground(void);
};
};

#endif
