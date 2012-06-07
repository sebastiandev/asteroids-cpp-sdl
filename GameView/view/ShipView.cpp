#include "ShipView.h"

using namespace view;

ShipView::ShipView(Entity *entity, SDLSurface* parentSurface, string accelerateImagePath) : EntityView(entity, parentSurface)
{
	accelerated = new SDLSurface();
	accelerated->loadFromImage(accelerateImagePath.c_str());
	temp = surface;
}

ShipView::ShipView(Entity *entity, SDLSurface* parentSurface, int width, int height, string accelerateImagePath) : EntityView(entity, parentSurface, width, height)
{
	accelerated = new SDLSurface();
	accelerated->loadFromImage(accelerateImagePath.c_str());
	temp = surface;
}

ShipView::~ShipView(void)
{
	delete accelerated;
}

void ShipView::setAcceleratingImage(string imagePath)
{
	this->acceleratingImage = imagePath;
}

string ShipView::getAcceleratingImage()
{
	return this->acceleratingImage;
}

void ShipView::paint(void)
{
	if (((Ship*)entity)->isAcelerated() && accelerated)
	{
		surface = accelerated;
		surface->rotate(entity->getRotation(), 1.0, 1); // rota para dejarla en la misma direccion que la anterior
	}
	else
	{
		surface = temp; // vuelve a poner la imagen original
		surface->rotate(entity->getRotation(), 1.0, 1); // rota para dejarla en la misma direccion que la anterior
	}

	EntityView::paint(); // llama al metodo de la clase padre que se encarga de pintar
}
