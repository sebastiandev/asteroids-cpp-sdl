#ifndef _SDLPANEL_H_
#define _SDLPANEL_H_

#include "SDLComponent.h"
#include "SDLScrollBar.h"
#include "Layout.h"
#include <list>

using namespace std;

namespace sdl
{
class Layout;
class SDLPanel : public SDLComponent
{
public:
	SDLPanel(SDLSurface*);
	SDLPanel(int, int, int, int, SDLSurface*);
	virtual ~SDLPanel(void);
	void addComponent(SDLComponent*);
	list<SDLComponent*> getComponents(void);
	bool isComponentSelected(void);
	SDLComponent* findSelectedComponent(void);
	virtual void updateViewport(Dimension*);
	void setScrollBar(SDLScrollBar*);
	SDLScrollBar* getScrollBar(void);
	bool hasScrollBar(void);
	void setLayout(Layout*);
	virtual void processEvent(SDLEvent*);
	virtual void draw(void);
private:
	void handleComponentSelection(SDLEvent*);
	list<SDLComponent*> components;
	SDLScrollBar* scrollBar;
	Layout* layout;
};
};

#endif
