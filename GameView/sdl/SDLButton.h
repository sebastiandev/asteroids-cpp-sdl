#ifndef _SDLBUTTON_H_
#define _SDLBUTTON_H_

#include "SDLComponent.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_ttf.h"
#include <string>

using namespace std;

namespace sdl
{
class SDLButton : public SDLComponent
{
public:
	SDLButton(string, SDLSurface*);
	SDLButton(int, int, int, int, string, SDLSurface*);
	virtual ~SDLButton(void);
	void setImage(SDLSurface*);
	virtual void draw(void);
protected:
	virtual void drawBorder(void);
	virtual void drawBackground(void);
	virtual void drawContents(void);
private:
	string text;
	SDLSurface* image;
	TTF_Font* font;
	//Se pone en true cuando se le da click y toma el foco
	bool isPressed;
};
};

#endif
