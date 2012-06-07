#ifndef _SDLTAB_H_
#define _SDLTAB_H_

#include "SDLComponent.h"
#include "SDLPanel.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_ttf.h"
#include <string>

using namespace std;

namespace sdl
{
class SDLTab : public SDLComponent
{
public:
	SDLTab(string, SDLPanel*, SDLSurface*);
	SDLTab(int, int, int, int, string, SDLPanel*, SDLSurface*);
	virtual ~SDLTab(void);
	void activate(void);
	void deactivate(void);
	bool isActivated(void);
	virtual void processEvent(SDLEvent*);
	virtual void draw(void);
private:
	string name;
	SDLPanel* panel;
	bool isActive;
};
};

#endif
