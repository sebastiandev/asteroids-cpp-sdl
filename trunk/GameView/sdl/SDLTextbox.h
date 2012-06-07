#ifndef _SDLTEXTBOX_H_
#define _SDLTEXTBOX_H_

#include "SDLComponent.h"
#include "SDL_ttf.h"
#include <string>

using namespace std;

namespace sdl
{
class SDLTextbox : public SDLComponent
{
public:
	SDLTextbox(SDLSurface*);
	SDLTextbox(int, int, int, int, SDLSurface*);
	virtual ~SDLTextbox(void);
	void setText(string);
	string getText(void);
	void addLetter(char);
	void deleteLetter(void);
	void addBlankLetter(void);
	virtual void processEvent(SDLEvent*);
	virtual void draw(void);
private:
	void initialized(void);
	string text;
	//Se pone en true cuando se le da click y toma el foco
	bool isEditable;
	int maxLettersOnDisplay;
	TTF_Font* font;
};
};

#endif
