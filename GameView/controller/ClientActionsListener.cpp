#include "ClientActionsListener.h"

using namespace view;
using namespace sdl;

ClientActionsListener::ClientActionsListener(void)
{
}

ClientActionsListener::~ClientActionsListener(void)
{
}

void ClientActionsListener::processMouseButtonPressed(SDLMouseEvent* sdlMouseEvent)
{
	/*cout << "El control de tipo '" << sdlMouseEvent->getSource()->getType() << "' ";
	cout << "cuyo nombre es '" << sdlMouseEvent->getSource()->getName() << "' ";
	cout << "produjo un evento de boton de mouse presionado atrapado por el controlador ClientActionsListener." << endl;*/
	cout << "Un evento de boton presionado de mouse llego a ClientActionsListener." << endl;
}

void ClientActionsListener::processMouseButtonReleased(SDLMouseEvent* sdlMouseEvent)
{
	cout << "Un evento de boton liberado de mouse llego a ClientActionsListener." << endl;
}
