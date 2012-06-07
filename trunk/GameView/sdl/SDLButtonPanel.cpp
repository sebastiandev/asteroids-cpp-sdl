#include "SDLButtonPanel.h"

using namespace sdl;

SDLButtonPanel::SDLButtonPanel(SDLSurface* surface) : SDLComponent(surface)
{
	name = "buttonpanel";
	type = SDLComponent::BUTTONPANEL;
}

SDLButtonPanel::~SDLButtonPanel(void)
{
	buttons.clear();
}

void SDLButtonPanel::addButton(SDLToggleButton* button)
{
	buttons.push_back(button);
}

bool SDLButtonPanel::isButtonSelected(void)
{
	bool found = false;
	list<SDLToggleButton*>::iterator it;
	for (it=buttons.begin(); it!=buttons.end() && !found; it++)
	{
		if ((*it)->isSelected())
		{
			found = true;
		}
	}
	return found;
}

SDLToggleButton* SDLButtonPanel::findSelectedButton(void)
{
	SDLToggleButton* selectedButton = NULL;
	bool found = false;
	list<SDLToggleButton*>::iterator it;
	for (it=buttons.begin(); it!=buttons.end() && !found; it++)
	{
		if ((*it)->isSelected())
		{
			selectedButton = *it;
			found = true;
		}
	}
	return selectedButton;
}

void SDLButtonPanel::processEvent(SDLEvent* sdlEvent)
{
	if (sdlEvent->getType() == SDLEvent::MOUSE_EVENT_TYPE)
	{
		SDLToggleButton* currentSelectedButton = findSelectedButton();
		bool selectedButtonFound = false;
		list<SDLToggleButton*>::iterator it;
		for (it=buttons.begin(); it!=buttons.end(); it++)
		{
			if (!selectedButtonFound)
			{
				(*it)->unSelect();
				(*it)->processEvent(sdlEvent);
				if ((*it)->isSelected())
				{
					selectedButtonFound = true;
				}
			}
			else
			{
				(*it)->unSelect();
			}
		}
		if (!selectedButtonFound && currentSelectedButton != NULL)
		{
			currentSelectedButton->select();
		}
	}
	SDLComponent::processEvent(sdlEvent);
}

void SDLButtonPanel::draw(void)
{
	list<SDLToggleButton*>::iterator it;
	for (it=buttons.begin(); it != buttons.end(); it++)
	{
		(*it)->draw();
	}
}
