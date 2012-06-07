#ifndef _CLIENTMOUSELISTENER_H_
#define _CLIENTMOUSELISTENER_H_

#include "..\sdl\MouseListener.h"
#include "..\sdl\event\SDLMouseEvent.h"
#include "..\sdl\SDLComponent.h"
#include <string>
#include <iostream>

using namespace sdl;
using namespace std;

namespace view
{
class ClientActionsListener : public MouseListener
{
public:
	ClientActionsListener(void);
	virtual ~ClientActionsListener(void);
	virtual void processMouseButtonPressed(SDLMouseEvent*);
	virtual void processMouseButtonReleased(SDLMouseEvent*);
};
};

#endif
