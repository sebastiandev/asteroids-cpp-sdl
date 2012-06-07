#ifndef _STARTWINDOW_H_
#define _STARTWINDOW_H_

#include "..\sdl\SDLSurface.h"
#include "..\sdl\SDLTabPanel.h"
#include "..\sdl\SDLPanel.h"
#include "..\sdl\SDLLabel.h"
#include "..\sdl\SDLTextbox.h"
#include "..\sdl\SDLButton.h"
#include "..\sdl\SDLButtonPanel.h"
#include "..\sdl\SDLToggleButton.h"
#include "..\sdl\SDLStatusBar.h"
#include "..\controller\ClientActionsListener.h"
#include "..\sdl\ScrollablePanelLayout.h"
#include <string>
#include <list>

using namespace sdl;
using namespace view;
using namespace std;

class StartWindow
{
public:
	StartWindow(ClientActionsListener* listener);
	virtual ~StartWindow(void);
	void addScenes(list<string> scenes);
	void show(void);
	SDLSurface* getSurface() { return surface;}
	string getClientHost() { return hostTextbox->getText();}
	string getClientPort() { return portTextbox->getText();}
	string getClientName() { return playerTextbox->getText();}
	string getSelectedShipName(void);
	string getServerPort() { return portTextboxServer->getText();}
	string getSceneName(void);
	
	bool isVisible() { return (quit == 0);}
	void close() { quit = 1;}
	
	void setStatus (string text);
private:
	void init(void);
	void handleEvents(void);
	void checkFramesPerSecond(void);
	void loop();
	void render(void);
	void handleEvent(SDL_Event);
	SDLSurface* surface;
	SDLTabPanel* tabPanel;
	SDLTextbox* hostTextbox;
	SDLTextbox* portTextbox;
	SDLTextbox* playerTextbox;
	SDLTextbox* portTextboxServer;
	SDLButtonPanel* shipsButtonPanel;
	SDLPanel* scenesPanel;
	SDLStatusBar* statusBar;
	Uint32 delayTime;
	Uint32 fps;
	Uint32 interval;
	int quit;
	ClientActionsListener* controller;
	list<string> sceneNames;
};

#endif;
