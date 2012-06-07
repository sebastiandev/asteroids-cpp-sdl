#include "SDLKeyboardEvent.h"

using namespace sdl::event;

SDLKeyboardEvent::SDLKeyboardEvent(SDL_Event* event) : SDLEvent(event)
{
	//(char)event->key.keysym.unicode;
	initializeKeyChar();
	initializeKeyCode();
	initializeModifierCode();
}

SDLKeyboardEvent::SDLKeyboardEvent(SDLEvent* sdlEvent)
{
	this->event = sdlEvent->getEvent();
	//(char)event->key.keysym.unicode;
	initializeKeyChar();
	initializeKeyCode();
	initializeModifierCode();
}

SDLKeyboardEvent::~SDLKeyboardEvent(void)
{
}

SDLKeyboardEvent::SDLKeyState SDLKeyboardEvent::getState(void)
{
	SDLKeyState state = KEY_PRESSED;
	if (event->key.state == SDL_RELEASED)
	{
		state = KEY_RELEASED;
	}
	return state;
}

char SDLKeyboardEvent::getKeyChar(void)
{
	return keyChar;
}

SDLKeyboardEvent::SDLKeyCode SDLKeyboardEvent::getKeyCode(void)
{
	return keyCode;
}

SDLKeyboardEvent::SDLKeyCode SDLKeyboardEvent::getModifierCode(void)
{
	return modifierCode;
}

void SDLKeyboardEvent::initializeKeyChar(void)
{
	keyChar = ' ';
	//if (keyChar == ' ')
	//{
		switch (event->key.keysym.sym)
		{
		case SDLK_a:
			keyChar = 'a';
			break;
		case SDLK_b:
			keyChar = 'b';
			break;
		case SDLK_c:
			keyChar = 'c';
			break;
		case SDLK_d:
			keyChar = 'd';
			break;
		case SDLK_e:
			keyChar = 'e';
			break;
		case SDLK_f:
			keyChar = 'f';
			break;
		case SDLK_g:
			keyChar = 'g';
			break;
		case SDLK_h:
			keyChar = 'h';
			break;
		case SDLK_i:
			keyChar = 'i';
			break;
		case SDLK_j:
			keyChar = 'j';
			break;
		case SDLK_k:
			keyChar = 'k';
			break;
		case SDLK_l:
			keyChar = 'l';
			break;
		case SDLK_m:
			keyChar = 'm';
			break;
		case SDLK_n:
			keyChar = 'n';
			break;
		case SDLK_o:
			keyChar = 'o';
			break;
		case SDLK_p:
			keyChar = 'p';
			break;
		case SDLK_q:
			keyChar = 'q';
			break;
		case SDLK_r:
			keyChar = 'r';
			break;
		case SDLK_s:
			keyChar = 's';
			break;
		case SDLK_t:
			keyChar = 't';
			break;
		case SDLK_u:
			keyChar = 'u';
			break;
		case SDLK_v:
			keyChar = 'v';
			break;
		case SDLK_w:
			keyChar = 'w';
			break;
		case SDLK_x:
			keyChar = 'x';
			break;
		case SDLK_y:
			keyChar = 'y';
			break;
		case SDLK_z:
			keyChar = 'z';
			break;
		case SDLK_0:
			keyChar = '0';
			break;
		case SDLK_1:
			keyChar = '1';
			break;
		case SDLK_2:
			keyChar = '2';
			break;
		case SDLK_3:
			keyChar = '3';
			break;
		case SDLK_4:
			keyChar = '4';
			break;
		case SDLK_5:
			keyChar = '5';
			break;
		case SDLK_6:
			keyChar = '6';
			break;
		case SDLK_7:
			keyChar = '7';
			break;
		case SDLK_8:
			keyChar = '8';
			break;
		case SDLK_9:
			keyChar = '9';
			break;

		case SDLK_KP0:
			keyChar = '0';
			break;
		case SDLK_KP1:
			keyChar = '1';
			break;
		case SDLK_KP2:
			keyChar = '2';
			break;
		case SDLK_KP3:
			keyChar = '3';
			break;
		case SDLK_KP4:
			keyChar = '4';
			break;
		case SDLK_KP5:
			keyChar = '5';
			break;
		case SDLK_KP6:
			keyChar = '6';
			break;
		case SDLK_KP7:
			keyChar = '7';
			break;
		case SDLK_KP8:
			keyChar = '8';
			break;
		case SDLK_KP9:
			keyChar = '9';
			break;

		case SDLK_PERIOD:
			keyChar = '.';
			break;
		case SDLK_KP_PERIOD:
			keyChar = '.';
			break;
		case SDLK_KP_MINUS:
			keyChar = '-';
			break;

		}
	//}
	//return keyChar;
}

void SDLKeyboardEvent::initializeKeyCode(void)
{
	keyCode = UNDEFINED;
	if (!isKeyChar())
	{
		switch (event->key.keysym.sym)
		{
		case SDLK_BACKSPACE:
			keyCode = BACKSPACE;
			break;
		case SDLK_SPACE:
			keyCode = SPACE;
			break;
		}
	}
	else
	{
		keyCode = KEY;
	}
}

void SDLKeyboardEvent::initializeModifierCode(void)
{
	modifierCode = UNDEFINED;
	switch (event->key.keysym.mod)
	{
	case KMOD_LSHIFT:
		modifierCode = SHIFT;
		break;
	case KMOD_RSHIFT:
		modifierCode = SHIFT;
		break;
	}
}

bool SDLKeyboardEvent::isKeyChar(void)
{
	bool isKey = false;
	if (keyChar != ' ')
	{
		isKey = true;
	}
	return isKey;
}
