#include "SDLTextbox.h"

using namespace sdl;

SDLTextbox::SDLTextbox(SDLSurface* surface) : SDLComponent(surface)
{
	this->name = "textbox";
	this->type = SDLComponent::TEXTBOX;
	this->text = "";
	this->isEditable = false;
	this->maxLettersOnDisplay = 20;
	//SDL_EnableUNICODE(SDL_ENABLE);
	initialized();
}

SDLTextbox::SDLTextbox(int xpos, int ypos, int w, int h, SDLSurface* surface) : SDLComponent(xpos, ypos, w, h, surface)
{
	this->name = "textbox";
	this->type = SDLComponent::TEXTBOX;
	this->text = "";
	this->isEditable = false;
	this->maxLettersOnDisplay = 20;
	//SDL_EnableUNICODE(SDL_DISABLE);
	initialized();
}

void SDLTextbox::initialized(void)
{
	font = TTF_OpenFont("..\\fonts\\arial.ttf", 18);
	if (!font)
	{
		string message("No es posible abrir el font arial.ttf. El error reportado por SDL es: '");
		message.append(TTF_GetError()).append("'.");
		Logger::instance().log(message);
	}
	else
	{
		height = TTF_FontHeight(font);
	}
}

SDLTextbox::~SDLTextbox(void)
{
	if (font != 0)
	{
		TTF_CloseFont(font);
	}
}

void SDLTextbox::setText(string text)
{
	this->text = text;
}

string SDLTextbox::getText()
{
	return text ;
}

void SDLTextbox::addLetter(char letter)
{
	text += letter;
}

void SDLTextbox::deleteLetter()
{
	text = text.substr(0, text.length()-1);
}

void SDLTextbox::addBlankLetter(void)
{
	text += ' ';
}

void SDLTextbox::processEvent(SDLEvent* sdlEvent)
{
	if (sdlEvent->getType() == SDLEvent::MOUSE_EVENT_TYPE)
	{
		SDLMouseEvent* mouseEvent = static_cast<SDLMouseEvent*>(sdlEvent);
		if (mouseEvent->getX() >= x && mouseEvent->getX() <= x+width &&
			mouseEvent->getY() >= y && mouseEvent->getY() <= y+height)
		{
			isEditable = true;
		}
		else
		{
			isEditable = false;
		}
	}
	if (sdlEvent->getType() == SDLEvent::KEYBOARD_EVENT_TYPE && isEditable)
	{
		SDLKeyboardEvent* keyboardEvent = new SDLKeyboardEvent(sdlEvent);
		if (keyboardEvent->getState() == SDLKeyboardEvent::KEY_PRESSED)
		{
			if (keyboardEvent->getKeyCode() == SDLKeyboardEvent::KEY)
			{
				if (keyboardEvent->getModifierCode() == SDLKeyboardEvent::SHIFT)
				{
					addLetter((char)toupper(keyboardEvent->getKeyChar()));
				}
				else
				{
					addLetter(keyboardEvent->getKeyChar());
				}
			}
			else if (keyboardEvent->getKeyCode() == SDLKeyboardEvent::SPACE)
			{
				addBlankLetter();
			}
			else if (keyboardEvent->getKeyCode() == SDLKeyboardEvent::BACKSPACE)
			{
				deleteLetter();
			}
		}
	}
	SDLComponent::processEvent(sdlEvent);
}

void SDLTextbox::draw(void)
{
	// Dibuja el marco del rectangulo
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = width;
	rectangle.h = height;
	SDL_FillRect(sdlSurface->getSurface(), &rectangle, SDL_MapRGB(sdlSurface->getSurface()->format, 100, 100, 100));

	// Dibuja el rectangulo
	if (isEditable)
	{
		rectangle.x = x+1;
		rectangle.y = y+1;
		rectangle.w = width-2;
		rectangle.h = height-2;
		SDL_FillRect(sdlSurface->getSurface(), &rectangle, SDL_MapRGB(sdlSurface->getSurface()->format, 230, 230, 230));
	}
	else
	{
		rectangle.x = x+1;
		rectangle.y = y+1;
		rectangle.w = width-2;
		rectangle.h = height-2;
		SDL_FillRect(sdlSurface->getSurface(), &rectangle, SDL_MapRGB(sdlSurface->getSurface()->format, 200, 200, 200));
	}

	if (font != 0)
	{
		TTF_SetFontStyle(font, 0);
		SDL_Color color = {255, 0, 0};

		string textToDisplay;
		if (text.length() > (unsigned int)maxLettersOnDisplay)
		{
			textToDisplay = text.substr(text.length()-maxLettersOnDisplay, text.length());
		}
		else
		{
			textToDisplay = text;
		}

		SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, textToDisplay.c_str(), color) ;
		if (textSurface != NULL)
		{
			SDL_Rect rectangle;
			rectangle.x = x + 10;
			rectangle.y = (height - textSurface->h) / 2 + y; //centra en y
			SDL_BlitSurface(textSurface, NULL, sdlSurface->getSurface(), &rectangle);
			SDL_FreeSurface(textSurface);
		}
	}
}