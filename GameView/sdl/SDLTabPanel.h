#ifndef _SDLTABPANEL_H_
#define _SDLTABPANEL_H_

#include "SDLComponent.h"
#include "SDLPanel.h"
#include "SDLTab.h"
#include <string>
#include <list>

using namespace std;

namespace sdl
{
class SDLTabPanel : public SDLComponent
{
public:
	SDLTabPanel(SDLSurface*);
	SDLTabPanel(int, int, int, int, SDLSurface*);
	virtual ~SDLTabPanel(void);
	void addTab(string, SDLPanel*);
	virtual void processEvent(SDLEvent*);
	virtual void draw(void);
private:
	SDLTab* findActiveTab(void);
	list<SDLTab*> tabs;
};
};

#endif
