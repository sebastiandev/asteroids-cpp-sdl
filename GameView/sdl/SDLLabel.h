#ifndef _SDLLABEL_H_
#define _SDLLABEL_H_

#include "SDLComponent.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_ttf.h"
#include <string>

using namespace std;

namespace sdl
{
class SDLLabel : public SDLComponent
{
public:
	SDLLabel(string, SDLSurface*);
	SDLLabel(string, int, SDLSurface*);
    SDLLabel(int, int, int, int, string, SDLSurface*);
	virtual ~SDLLabel(void);
	virtual void draw(void);
	string getText(void);
	void setText(string);
protected:
	void initialize(void);
	string text;
	int textSize;
	TTF_Font* font;
};
};

#endif
