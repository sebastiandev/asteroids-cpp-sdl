#ifndef _SDLBUTTONPANEL_H_
#define _SDLBUTTONPANEL_H_

#include "SDLComponent.h"
#include "SDLToggleButton.h"
#include <list>

using namespace sdl;

namespace sdl
{
class SDLButtonPanel : public SDLComponent
{
public:
	SDLButtonPanel(SDLSurface*);
	virtual ~SDLButtonPanel(void);
	void addButton(SDLToggleButton*);
	bool isButtonSelected(void);
	SDLToggleButton* findSelectedButton(void);
	virtual void processEvent(SDLEvent*);
	virtual void draw(void);
private:
	list<SDLToggleButton*> buttons;
};
};

#endif
