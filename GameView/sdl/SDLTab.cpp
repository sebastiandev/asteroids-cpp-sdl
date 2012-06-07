#include "SDLTab.h"

using namespace sdl;

SDLTab::SDLTab(string name, SDLPanel* panel, SDLSurface* surface) : SDLComponent(surface)
{
	this->name = name;
	this->type = SDLComponent::TAB;
	this->panel = panel;
	this->isActive = false;
}

SDLTab::SDLTab(int xpos, int ypos, int w, int h, string name, SDLPanel* panel, SDLSurface* surface) : SDLComponent(xpos, ypos, w, h, surface)
{
	this->name = name;
	this->type = SDLComponent::TAB;
	this->panel = panel;
	this->isActive = false;
}

SDLTab::~SDLTab(void)
{
	delete panel;
}

void SDLTab::activate(void)
{
	this->isActive = true;
}

void SDLTab::deactivate(void)
{
	this->isActive = false;
}

bool SDLTab::isActivated(void)
{
	return isActive;
}

void SDLTab::processEvent(SDLEvent* sdlEvent)
{
	if (panel != 0)
	{
		panel->processEvent(sdlEvent);
	}
	SDLComponent::processEvent(sdlEvent);
}

void SDLTab::draw(void)
{
	short xs[4], ys[4];
	xs[0] = x; //punto inicial
	xs[1] = xs[0] + 10; // segundo vertice 10px mas adelante
	xs[2] = xs[1] + 60; // tercer vertice 60px mas adelante
	xs[3] = xs[2] + 10; // cuarto vertice 10px mas adelante, completando 80 px de ancho

	ys[0] = y+20; // primer vertice de y, inicio de tab
	ys[1] = y; // segundo vertice, aumenta altura para la forma del tab. 20px de alto
	ys[2] = y; // tercer vertice, misma altura anterior
	ys[3] = y+20;// cuarto vertice, baja para cerrar el poligono del tab
	
	if (this->isActive)
	{
		filledPolygonRGBA(sdlSurface->getSurface(), xs, ys, 4, 232, 232, 232, 255);
	}
	else
	{
		filledPolygonRGBA(sdlSurface->getSurface(), xs, ys, 4, 176, 176, 176, 255);
	}

	// dibuja el marco del tab
	//aapolygonRGBA(sdlSurface->getSurface(), xs, ys, 4, 89, 89, 89, 255);

	// pinta letras del tab
	TTF_Font* font = TTF_OpenFont("..\\fonts\\arial.ttf", 14);
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
		SDL_Surface* textSurface = TTF_RenderUTF8_Blended(font, this->name.c_str(), color) ;
		
		if (textSurface != NULL)
		{
			SDL_Rect rectangle;
			rectangle.x = (width - textSurface->w) / 2  + x; //centra en x
			rectangle.y = y;
			SDL_BlitSurface(textSurface, NULL, sdlSurface->getSurface(), &rectangle);
			SDL_FreeSurface(textSurface);
		}
		TTF_CloseFont(font);
	}
	if (isActivated())
	{
		this->panel->draw();
	}
}
