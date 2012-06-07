#ifndef _SDLCOMPONENT_H_
#define _SDLCOMPONENT_H_

#include "SDLSurface.h"
#include "Viewport.h"
#include "MouseListener.h"
#include "KeyboardListener.h"
#include "event\SDLEvent.h"
#include "event\SDLMouseEvent.h"
#include "event\SDLKeyboardEvent.h"
#include "Logger.h"
#include "SDL.h"

using namespace util;
using namespace sdl::event;

namespace sdl
{
class SDLComponent
{
public:
	SDLComponent(SDLSurface*);
	SDLComponent(int, int, int, int, SDLSurface*);
	virtual ~SDLComponent(void);

	typedef enum ComponentType
	{
		COMPONENT,
		BUTTON,
		TOGGLEBUTTON,
		LABEL,
		STATUSBAR,
		PANEL,
		BUTTONPANEL,
		SCROLLBAR,
		TAB,
		TABPANEL,
		TEXTBOX
	};

	ComponentType getType(void);
	void setName(string);
	string getName(void);
	void setX(int);
	int getX(void);
	void setY(int);
	int getY(void);
	void setWidth(int);
	int getWidth(void);
	void setHeight(int);
	int getHeight(void);
	Viewport* getViewport(void);
	void show(void);
	void hide(void);
	bool isVisible(void);
	void select(void);
	void unSelect(void);
	bool isSelected(void);
	virtual void updateViewport(Dimension*);
	void setMouseListener(MouseListener*);
	void setKeyboardListener(KeyboardListener*);
	Color* getBackgroundColor(void);
	void setBackgroundColor(Color*);
	void setSelectedBackgroundColor(Color*);
	virtual void processEvent(SDLEvent*);
	virtual void draw(void)=0;
protected:
	bool isHandleKeyboardEvent(SDLEvent*);
	bool isHandleMouseEvent(SDLEvent*);
	Dimension clipToViewport(void);
	SDLSurface* sdlSurface;
	Viewport* viewport;
	MouseListener* mouseListener;
	KeyboardListener* keyboardListener;
	ComponentType type;
	string name;
	int x;
	int y;
	int width;
	int height;
	bool _isSelected;
	bool _isVisible;
	Color* backgroundColor;
	Color* selectedBackgroundColor;
};
};

#endif
