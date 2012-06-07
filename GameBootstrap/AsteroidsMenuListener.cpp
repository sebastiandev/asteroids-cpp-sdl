#include "AsteroidsMenuListener.h"
#include "Bootstrap.h"

AsteroidsMenuListener::AsteroidsMenuListener(Bootstrap *_controller) : controller(_controller)
{
}

AsteroidsMenuListener::~AsteroidsMenuListener(void)
{
}

void AsteroidsMenuListener::processMouseButtonPressed(SDLMouseEvent* e)
{
	if (e && e->getSource() && e->getSource()->getName().compare("Cliente::Conectar") == 0)
	{
		cout << "cliente quiere conectar" << endl;
		controller->launchClient();
	}
	else if (e && e->getSource() && e->getSource()->getName().compare("Cliente::Salir") == 0)
	{
		cout << "cliente quiere salir" << endl;
		controller->quit();
	}
	else if (e && e->getSource() && e->getSource()->getName().compare("Server::Conectar") == 0)
	{
		cout << "server quiere conectar" << endl;
		controller->launchServer();
	}
	else if (e && e->getSource() && e->getSource()->getName().compare("Server::Salir") == 0)
	{
		cout << "server quiere salir" << endl;
		controller->quit();
	}
	else if (e && e->getSource() && e->getSource()->getName().compare("Cliente::Nave1") == 0)
	{
		cout << "cliente elige nave1" << endl;
		controller->setSelectedShip("nave1");
	}
		else if (e && e->getSource() && e->getSource()->getName().compare("Cliente::Nave2") == 0)
	{
		cout << "cliente elige nave2" << endl;
		controller->setSelectedShip("nave2");
	}
	else if (e && e->getSource() && e->getSource()->getName().compare("Cliente::Nave3") == 0)
	{
		cout << "cliente elige nave3" << endl;
		controller->setSelectedShip("nave3");
	}
	else if (e && e->getSource() && e->getSource()->getName().compare("Cliente::Nave4") == 0)
	{
		cout << "cliente elige nave4" << endl;
		controller->setSelectedShip("nave4");
	}
	else if (e && e->getSource() && e->getSource()->getName().compare("Cliente::Nave5") == 0)
	{
		cout << "cliente elige nave5" << endl;
		controller->setSelectedShip("nave5");
	}

}

void AsteroidsMenuListener::processMouseButtonReleased(SDLMouseEvent* e)
{

}
