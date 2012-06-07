#include "SDLTabPanel.h"

using namespace sdl;

SDLTabPanel::SDLTabPanel(SDLSurface* surface) : SDLComponent(surface)
{
	this->name = "tabpanel";
	this->type = SDLComponent::TABPANEL;
}

SDLTabPanel::SDLTabPanel(int xpos, int ypos, int w, int h, SDLSurface* surface) : SDLComponent(xpos, ypos, w, h, surface)
{
	this->name = "tabpanel";
	this->type = SDLComponent::TABPANEL;
}

SDLTabPanel::~SDLTabPanel(void)
{
	tabs.clear();
}

void SDLTabPanel::addTab(string name, SDLPanel* panel)
{
	int xpos = x+(tabs.size()*80);
	int ypos = y+10;
	int tabWidth = 80;
	int tabHeight = 20;

	panel->setX(x);
	panel->setY(ypos+tabHeight);
	panel->setWidth(width);
	panel->setHeight(height-tabHeight);
	Dimension d(x, ypos+tabHeight, width, height-tabHeight);
	panel->updateViewport(&d);

	SDLTab* tab = new SDLTab(xpos, ypos, tabWidth, tabHeight, name, panel, sdlSurface);
	//Activa solo el primer tab que se agrega
	if (tabs.empty())
	{
		tab->activate();
	}
	tabs.push_back(tab);
}

void SDLTabPanel::processEvent(SDLEvent* sdlEvent)
{
	list<SDLTab*>::iterator it;
	for (it=tabs.begin(); it!=tabs.end(); it++)
	{
		if (sdlEvent->getType() == SDLEvent::MOUSE_EVENT_TYPE)
		{
			SDLMouseEvent* mouseEvent = static_cast<SDLMouseEvent*>(sdlEvent);
			if (mouseEvent->getX() >= (*it)->getX() && mouseEvent->getX() <= (*it)->getX()+(*it)->getWidth() &&
				mouseEvent->getY() >= (*it)->getY() && mouseEvent->getY() <= (*it)->getY()+(*it)->getHeight())
			{
				SDLTab* activeTab = findActiveTab();
				activeTab->deactivate();
				(*it)->activate();
			}
		}
		if ((*it)->isActivated())
		{
			(*it)->processEvent(sdlEvent);
		}
	}
	SDLComponent::processEvent(sdlEvent);
}

void SDLTabPanel::draw(void)
{
	list<SDLTab*>::iterator it;
	for (it=tabs.begin(); it!=tabs.end(); it++)
	{
		(*it)->draw();
	}
}

SDLTab* SDLTabPanel::findActiveTab(void)
{
	SDLTab* activeTab;
	list<SDLTab*>::iterator it;
	for (it=tabs.begin(); it!=tabs.end(); it++)
	{
		if ((*it)->isActivated())
		{
			activeTab = *it;
		}
	}
	return activeTab;
}
