#include "SDLButton.h"

using namespace sdl;

SDLButton::SDLButton(string text, SDLSurface* surface) : SDLComponent(surface)
{
	name = "button";
	type = SDLComponent::BUTTON;
	this->text = text;
	isPressed = false;
	image = NULL;
	font = TTF_OpenFont("..\\fonts\\arial.ttf", 18);
}

SDLButton::SDLButton(int xpos, int ypos, int w, int h, string text, SDLSurface* surface) : SDLComponent(xpos, ypos, w, h, surface)
{
	name = "button";
	type = SDLComponent::BUTTON;
	this->text = text;
	isPressed = false;
	image = NULL;
	font = TTF_OpenFont("..\\fonts\\arial.ttf", 18);
}

SDLButton::~SDLButton(void)
{
	delete image;
	TTF_CloseFont(font);
}

void SDLButton::setImage(SDLSurface* image)
{
	this->image = image;
}

void SDLButton::draw(void)
{
	drawBorder();
	drawBackground();
	drawContents();
}

void SDLButton::drawBorder(void)
{
	roundedBoxRGBA(sdlSurface->getSurface(), x, y, x+width, y+height, 10, 100, 100, 100, 255);
}

void SDLButton::drawBackground(void)
{
	roundedBoxRGBA(sdlSurface->getSurface(), x+1, y+1, x+width-1, y+height-1, 10, 200, 200, 200, 255);
}

void SDLButton::drawContents(void)
{
	if (image != NULL)
	{ 
		sdlSurface->draw(image, x+10, y+10);
	}
	else
	{		
		if (!font)
		{
			string message("No es posible abrir el font arial.ttf. El error reportado por SDL es: '");
			message.append(SDL_GetError()).append("'.");
			Logger::instance().log(message);
		}
		else
		{
			TTF_SetFontStyle(font, 0);
			SDL_Color color = {0, 0, 0};
			SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, this->text.c_str(), color) ;
		
			if (textSurface != NULL)
			{
				SDL_Rect rectangle;
				rectangle.x = (width - textSurface->w) / 2  + x; //centra en x
				rectangle.y = (height - textSurface->h) / 2  + y; //centra en y
				SDL_BlitSurface(textSurface, NULL, sdlSurface->getSurface(), &rectangle);
				SDL_FreeSurface(textSurface);
			}			
		}
	}
}
