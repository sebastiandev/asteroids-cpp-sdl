#ifndef _ASTEROIDSMENULISTENER_H_
#define _ASTEROIDSMENULISTENER_H_

#include "..\GameView\controller\ClientActionsListener.h"

class Bootstrap;

class AsteroidsMenuListener : public view::ClientActionsListener
{
public:
	AsteroidsMenuListener(Bootstrap *controller);
	~AsteroidsMenuListener(void);

	void processMouseButtonPressed(SDLMouseEvent*);
	void processMouseButtonReleased(SDLMouseEvent*);


private:

	Bootstrap *controller;
};

#endif