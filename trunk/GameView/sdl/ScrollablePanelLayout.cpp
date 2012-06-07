#include "ScrollablePanelLayout.h"

using namespace sdl;

ScrollablePanelLayout::ScrollablePanelLayout(void)
{
}

ScrollablePanelLayout::~ScrollablePanelLayout(void)
{
}

void ScrollablePanelLayout::applyLayout(SDLPanel* panel)
{
	int increment = 0;
	int ypos = panel->getY();
	if (panel->hasScrollBar())
	{
		increment = panel->getScrollBar()->getIncrement();
	}
	list<SDLComponent*>::iterator it;
	list<SDLComponent*> components = panel->getComponents();
	for (it=components.begin(); it!=components.end(); it++)
	{
		if (increment >= (*it)->getHeight())
		{
			increment -= (*it)->getHeight();
			(*it)->hide();
		}
		else
		{
			(*it)->setX(panel->getX());
			(*it)->setY(ypos);
			(*it)->setWidth(panel->getWidth());
			(*it)->show();
			ypos += (*it)->getHeight();
		}
	}
}
