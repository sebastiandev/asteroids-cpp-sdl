#ifndef _SDLSURFACE_H_
#define _SDLSURFACE_H_

#include "Color.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_rotozoom.h"

namespace sdl
{
class SDLSurface
{
public:
	SDLSurface(void);
	SDLSurface(int, int, int, Uint32 flags=HARDMEMORY | DOUBLE_BUFFER | RESIZABLE);
	virtual ~SDLSurface(void);

	typedef enum videoMode
	{
		SOFTMEMORY = 0x00000000, 
		HARDMEMORY = 0x00000001, 
		ASYNCPAINT = 0x00000004, 
		ANYFORMAT = 0x10000000, 
		PALETTE_ACCESS = 0x20000000, 
		DOUBLE_BUFFER = 0x40000000, 
		FULLSCREEN = 0x80000000,
		OPENGL = 0x00000002,
		OPENGL_PAINT = 0x0000000A,
		RESIZABLE = 0x00000010,
		NOFRAME = 0x00000020
	};

	int getOriginalWidth(void);
	int getOriginalHeight(void);
	int getWidth(void);
	int getHeight(void);
	bool resetVideoMode(int, int, int, Uint32 flags=HARDMEMORY | DOUBLE_BUFFER | RESIZABLE);
	bool loadFromImage(const char* file);
    bool draw(SDLSurface* srfc, double x, double y);
	bool drawImage(char* imageFile, double x, double y);
	void paint(void);
	void rotate(double angle, double zoom, int smooth);
	void scale(double widthPercentaje, double heightPercentage);
	bool isRotated(void);
	SDL_Surface* getSurface(void);
	void setBackgroundColor(Color*);

protected:
	static bool initialized;
	SDL_Surface* surface;
	SDL_Surface* rotatedSurface;
	bool rotated;
	Color *bgcolor;
};
};

#endif
