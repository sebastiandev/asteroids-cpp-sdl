#include "SDLSurface.h"

using namespace sdl;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
#else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
#endif

bool SDLSurface::initialized = false;

SDLSurface::SDLSurface(void)
{
	surface = NULL;
	rotatedSurface = NULL;
	rotated = false;
}

SDLSurface::SDLSurface(int width, int height, int depth, Uint32 flags)
{
	if (!initialized)
	{
		SDL_WM_SetCaption("Asteroids Game", "Asteroids Game");
		surface = SDL_SetVideoMode(width, height, depth, flags);
		initialized = true;
	}
	else
	{
		surface = SDL_CreateRGBSurface(HARDMEMORY, width, height, depth, rmask, gmask, bmask, amask);
	}
	rotatedSurface = NULL;
	rotated = false;
}

SDLSurface::~SDLSurface(void)
{
	SDL_FreeSurface(surface);
	SDL_FreeSurface(rotatedSurface);
}

int SDLSurface::getOriginalWidth()
{
	return surface->w;
}

int SDLSurface::getOriginalHeight()
{
	return surface->h;
}

int SDLSurface::getWidth(void)
{
	return getSurface()->w;
}

int SDLSurface::getHeight(void)
{
	return getSurface()->h;
}

void SDLSurface::setBackgroundColor(Color* color)
{
	this->bgcolor = new Color(*color);
	SDL_FillRect(surface, &surface->clip_rect, SDL_MapRGB(surface->format, color->getRed(), color->getGreen(), color->getBlue()));
}

bool SDLSurface::resetVideoMode(int width, int height, int depth, Uint32 flags)
{
	SDL_Surface *aux = SDL_SetVideoMode(width, height, depth, flags);
	if (!aux)
	{
		return false;
	}
	SDL_FreeSurface(surface);
	surface = aux;
	
	if (bgcolor)
		setBackgroundColor(bgcolor);//setea el mismo color de fondo

	return true;
}

bool SDLSurface::loadFromImage(const char* file)
{
	SDL_Surface* temp = NULL;
	if ((temp = IMG_Load(file)) == NULL)
	{
        return false;
    }
 
	SDL_FreeSurface(surface);
    surface = SDL_DisplayFormatAlpha(temp);
	
    SDL_FreeSurface(temp);
	return true;
}

bool SDLSurface::drawImage(char* imageFile, double x, double y)
{
	if (imageFile == NULL || surface == NULL)
	{
		return false;
	}
    SDL_Surface* temp = NULL;
	SDL_Surface* aux  = NULL;
 
	if ((temp = IMG_Load(imageFile)) == NULL)
	{
        return false;
    }
    aux = SDL_DisplayFormatAlpha(temp);
    
	SDL_Rect DestR;
    DestR.x = (Sint16)x;
    DestR.y = (Sint16)y;
	SDL_BlitSurface(aux, NULL, getSurface(), &DestR);

    SDL_FreeSurface(temp);
	SDL_FreeSurface(aux);
	return true;
}

bool SDLSurface::draw(SDLSurface* srfc, double x, double y)
{
	if (getSurface() == NULL || srfc->getSurface() == NULL)
	{
		return false;
	}
    SDL_Rect DestR;
    DestR.x = (Sint16)x;
    DestR.y = (Sint16)y;
	SDL_BlitSurface(srfc->getSurface(), NULL, getSurface(), &DestR);
    return true;
}

//Adding the rotate image method
//Angle from 0 to 360, zoom should be 1, smooth 0.
void SDLSurface::rotate(double angle, double zoom, int smooth)
{
   	if (isRotated())
	{
		SDL_FreeSurface(rotatedSurface);
	}
	if (angle != 0)
	{
		rotated = true;
	}
	else
	{
		// no rotar nada y poner el flag en false para usa la imagen original!
		rotated = false;
		return;
	}

	//give initial for rotate image
    SDL_Surface* rotatefile = NULL;

    //get rotate here
    rotatefile = rotozoomSurface(surface, angle, zoom, smooth);

    //get optimizing
    rotatedSurface = SDL_DisplayFormatAlpha(rotatefile);
    SDL_FreeSurface(rotatefile);
}

bool SDLSurface::isRotated(void)
{
	return rotated;
}

void SDLSurface::scale(double widthPercentaje, double heightPercentage)
{	
	if (heightPercentage != 1.0 || widthPercentaje != 1.0)
	{
		SDL_Surface *aux = zoomSurface(getSurface(), widthPercentaje, heightPercentage, 1);
		SDL_FreeSurface(getSurface());//libera el surface anterior
		if (isRotated())
		{
			rotatedSurface = aux;
		}
		else
		{
			surface = aux;
		}
	}
}

void SDLSurface::paint(void)
{
	SDL_Flip(getSurface());
}

SDL_Surface* SDLSurface::getSurface(void)
{
	if (isRotated() && rotatedSurface)
	{
		return rotatedSurface;
	}
	return surface;
}
