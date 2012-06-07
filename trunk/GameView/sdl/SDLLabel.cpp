#include "SDLLabel.h"

using namespace sdl;

SDLLabel::SDLLabel(string text, SDLSurface* surface) : SDLComponent(surface)
{
	name = "label";
	type = SDLComponent::LABEL;
	this->text = text;
	textSize = 18;
	initialize();
}

SDLLabel::SDLLabel(string text, int size, SDLSurface* surface) : SDLComponent(surface)
{
	name = "label";
	type = SDLComponent::LABEL;
	this->text = text;
	textSize = size;
	initialize();
}

SDLLabel::SDLLabel(int xpos, int ypos, int w, int h, string text, SDLSurface* surface) : SDLComponent(xpos, ypos, w, h, surface)
{
	name = "label";
	type = SDLComponent::LABEL;
	this->text = text;
	textSize = 18;
	initialize();
}

void SDLLabel::initialize(void)
{
	font = TTF_OpenFont("..\\fonts\\arial.ttf", textSize);
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

SDLLabel::~SDLLabel(void)
{
	if (font != 0)
	{
		TTF_CloseFont(font);
	}
}

void SDLLabel::draw(void)
{
	bool isVisible = false;
	Dimension labelViewport = clipToViewport();
	if (labelViewport.getX() >= viewport->getX() &&
		labelViewport.getX()+labelViewport.getWidth() <= viewport->getX()+viewport->getWidth() &&
		labelViewport.getY() >= viewport->getY() &&
		labelViewport.getY()+labelViewport.getHeight() <= viewport->getY()+viewport->getHeight())
	{
		isVisible = true;
	}
	if (isVisible && font != 0)
	{
		if (isSelected() && selectedBackgroundColor != NULL && selectedBackgroundColor->getAlpha() == 0)
		{
			boxRGBA(sdlSurface->getSurface(), x, y, x+viewport->getWidth(), y+height, selectedBackgroundColor->getRed(),
				selectedBackgroundColor->getGreen(), selectedBackgroundColor->getBlue(), 255);
		}
		else if (backgroundColor != NULL && backgroundColor->getAlpha() == 0)
		{
			boxRGBA(sdlSurface->getSurface(), x, y, x+viewport->getWidth(), y+height, backgroundColor->getRed(), backgroundColor->getGreen(),
				backgroundColor->getBlue(), 255);
		}

		TTF_SetFontStyle(font, 0);
		SDL_Color color = {0, 0, 0};
		SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color) ;
		if (textSurface != NULL)
		{
			SDL_Rect source;
			source.x = 0;
			source.y = 0;
			source.w = viewport->getWidth();
			source.h = height;

			SDL_Rect destination;
			destination.x = x;
			destination.y = y;
			destination.w = viewport->getWidth();
			destination.h = height;
			SDL_BlitSurface(textSurface, &source, sdlSurface->getSurface(), &destination);
			SDL_FreeSurface(textSurface);
		}
	}
}

string SDLLabel::getText(void)
{
	return text;
}

void SDLLabel::setText(string text)
{
	this->text = text;
}
