#include "SDLPanel.h"

using namespace sdl;

SDLPanel::SDLPanel(SDLSurface* surface) : SDLComponent(surface)
{
	this->name = "panel";
	this->type = SDLComponent::PANEL;
	scrollBar = NULL;
	layout = NULL;
}

SDLPanel::SDLPanel(int xpos, int ypos, int w, int h, SDLSurface* surface) : SDLComponent(xpos, ypos, w, h, surface)
{
	this->name = "panel";
	this->type = SDLComponent::PANEL;
	scrollBar = NULL;
	layout = NULL;
}

SDLPanel::~SDLPanel(void)
{
	delete scrollBar;
	delete layout;
	components.clear();
}

void SDLPanel::addComponent(SDLComponent* component)
{
	int viewportWidth = width;
	if (scrollBar != NULL)
	{
		scrollBar->setMaximumIncrement(scrollBar->getMaximumIncrement()+component->getHeight());
		viewportWidth -= scrollBar->getWidth();
	}
	Dimension d(x, y, viewportWidth, height);
	component->updateViewport(&d);
	components.push_back(component);
}

list<SDLComponent*> SDLPanel::getComponents(void)
{
	return components;
}

bool SDLPanel::isComponentSelected(void)
{
	bool found = false;
	list<SDLComponent*>::iterator it;
	for (it=components.begin(); it!=components.end() && !found; it++)
	{
		if ((*it)->isSelected())
		{
			found = true;
		}
	}
	return found;
}

SDLComponent* SDLPanel::findSelectedComponent(void)
{
	SDLComponent* selectedComponent = NULL;
	bool found = false;
	list<SDLComponent*>::iterator it;
	for (it=components.begin(); it!=components.end() && !found; it++)
	{
		if ((*it)->isSelected())
		{
			selectedComponent = *it;
			found = true;
		}
	}
	return selectedComponent;
}

void SDLPanel::updateViewport(Dimension* d)
{
	SDLComponent::updateViewport(d);
	int viewportWidth = width;
	if (scrollBar != NULL)
	{
		viewportWidth -= scrollBar->getWidth();
	}
	Dimension panelDimension(x, y, viewportWidth, height);
	Dimension* componentViewport = panelDimension.intersect(d);
	list<SDLComponent*>::iterator it;
	for (it=components.begin(); it!=components.end(); it++)
	{
		(*it)->updateViewport(componentViewport);
	}
	delete componentViewport;
}

void SDLPanel::setScrollBar(SDLScrollBar* sb)
{
	scrollBar = sb;
	scrollBar->setX(x+width-20);
	scrollBar->setY(y);
	scrollBar->setWidth(20);
	scrollBar->setHeight(height);

	int maximumIncrement = 0;
	list<SDLComponent*>::iterator it;
	for (it=components.begin(); it!=components.end(); it++)
	{
		maximumIncrement += (*it)->getHeight();
	}
	scrollBar->setMaximumIncrement(maximumIncrement-height);
}

SDLScrollBar* SDLPanel::getScrollBar(void)
{
	return scrollBar;
}

bool SDLPanel::hasScrollBar(void)
{
	return (scrollBar != NULL);
}

void SDLPanel::setLayout(Layout* layout)
{
	this->layout = layout;
}

void SDLPanel::processEvent(SDLEvent* sdlEvent)
{
	if (scrollBar != NULL)
	{
		scrollBar->processEvent(sdlEvent);
		handleComponentSelection(sdlEvent);
	}
	list<SDLComponent*>::iterator it;
	for (it=components.begin(); it!=components.end(); it++)
	{
		(*it)->processEvent(sdlEvent);
	}
	SDLComponent::processEvent(sdlEvent);
}

void SDLPanel::draw(void)
{
	boxRGBA(sdlSurface->getSurface(), x, y, x+width, y+height, 232, 232, 232, 255);
	int increment = 0;
	if (layout != NULL)
	{
		layout->applyLayout(this);
	}
	list<SDLComponent*>::iterator it;
	for (it=components.begin(); it!=components.end(); it++)
	{
		if ((*it)->isVisible())
		{
			(*it)->draw();
		}
	}
	if (scrollBar != NULL)
	{
		scrollBar->draw();
	}
}

void SDLPanel::handleComponentSelection(SDLEvent* sdlEvent)
{
	if (sdlEvent->getType() == SDLEvent::MOUSE_EVENT_TYPE)
	{
		Dimension panelDimension(x, y, width-scrollBar->getWidth(), height);
		Dimension* d = viewport->intersect(&panelDimension);
		SDLMouseEvent* mouseEvent = static_cast<SDLMouseEvent*>(sdlEvent);
		if (mouseEvent->getX() >= d->getX() && mouseEvent->getX() <= d->getX()+d->getWidth() &&
			mouseEvent->getY() >= d->getY() && mouseEvent->getY() <= d->getY()+d->getHeight())
		{
			bool found = false;
			list<SDLComponent*>::iterator it;
			for (it=components.begin(); it!=components.end(); it++)
			{
				if (mouseEvent->getX() >= (*it)->getX() && mouseEvent->getX() <= (*it)->getX()+(*it)->getWidth() &&
					mouseEvent->getY() >= (*it)->getY() && mouseEvent->getY() <= (*it)->getY()+(*it)->getHeight() && !found)
				{
					(*it)->select();
					found = true;
				}
				else
				{
					(*it)->unSelect();
				}
			}
		}
		delete d;
	}
}
