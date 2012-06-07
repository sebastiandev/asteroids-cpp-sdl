#include "EntityView.h"

using namespace view;

EntityView::EntityView(Entity* entity, SDLSurface* parentSurface)
{
	init(entity, parentSurface);
}

EntityView::EntityView(Entity* entity, SDLSurface* parentSurface, int width, int height)
{
	init(entity, parentSurface);

	if ((width > 0) && (height > 0) && (surface->getOriginalWidth() > 0) && (surface->getOriginalHeight() > 0))
	{
		// escalar imagen
		double xfactor = ((double)width / (double)surface->getOriginalWidth());
		double yfactor = ((double)height / (double)surface->getOriginalHeight());
		surface->scale(xfactor, yfactor);
	}
}

EntityView::EntityView(Entity* entity, SDLSurface* parentSurface, SDLSurface* srfc)
{
	this->entity = entity;
	this->parentSurface = parentSurface;
	surface = srfc;
}

void EntityView::init(Entity* entity, SDLSurface* parentSurface)
{
	this->entity = entity;
	this->parentSurface = parentSurface;
	this->lastDirection = 0.0;

	surface = new SDLSurface();
	surface->loadFromImage(entity->getImagePath().c_str());

}

EntityView::~EntityView(void)
{
	delete surface;
}

void EntityView::setPosition(double x, double y)
{
	this->entity->setPosition(x, y);
}

double EntityView::getX(void)
{
	return entity->getX();
}

double EntityView::getY(void)
{
	return entity->getY();
}

double EntityView::getWidth()
{
	return surface->getWidth();
}

double EntityView::getHeight()
{
	return surface->getHeight();
}

void EntityView::paint(void)
{
	if (entity)
	{
		double x = entity->getX();
		double y = entity->getY();

		// solamente rota si cambio el angulo (son calculos costosos)
		if (lastDirection != entity->getRotation())
		{
			surface->rotate(entity->getRotation(), 1.0, 1);
			lastDirection = entity->getRotation();
		}

		if (surface->isRotated())
		{
			// tenemos que corregir la posicion de la imagen, porque al rotarla
			// la imagen crece en alto y ancho
			x = entity->getX() - (surface->getWidth() - surface->getOriginalWidth())/2;
			y = entity->getY() - (surface->getHeight() - surface->getOriginalHeight())/2;
		}

		if (parentSurface)
			parentSurface->draw(surface, x, y); // pintado original

		// las entidades no se pintan mas en ambos margenes para evitar problemas en las colisiones
		// hasta que no sale completamente, no vuelve a aparecer del otro lado
		//checkAndPaintEntityOnEdge(x, y); // pintado de partes de entidades en bordes
	}
}

void EntityView::checkAndPaintEntityOnEdge(double rotatedX, double rotatedY)
{
	/****************************************************************************** 
	   Lógica para que cuando una entidad comienza a salir de la pantalla, 
	   vaya apareciendo por el otro lado. En las esquinas se pinta la parte
	   saliente de la entidad en las otras 3 esquinas, hasta que sale por completo
	   y aparece en la esquina opuesta
	******************************************************************************/
	// chequea para pintar el resto de las partes de la imagen
	// si sale una parte por el margen derecho, aparece otra parte por el izq
	if (rotatedX+surface->getWidth() > parentSurface->getWidth())
	{
		parentSurface->draw(surface, rotatedX-parentSurface->getWidth(), rotatedY);
	}
	else if (rotatedX < 0)
	{
		// si sale una parte por el margen izq, aparece otra parte por el derecho
		parentSurface->draw(surface, rotatedX+parentSurface->getWidth(), rotatedY);
	}

	if (rotatedY+surface->getHeight() > parentSurface->getHeight())
	{
		// si sale una parte por el margen inferior, aparece otra parte por el superior
		parentSurface->draw(surface, rotatedX, rotatedY-parentSurface->getHeight());
	}
	else if (rotatedY < 0)
	{
		// si sale una parte por el margen superior, aparece otra parte por el inferior
		parentSurface->draw(surface, rotatedX, rotatedY+parentSurface->getHeight());
	}
	
	// chequea las esquinas para pintar enel vertice opuesto
	// esquina superior izq
	if (rotatedX < 0 && rotatedY < 0)
	{
		parentSurface->draw(surface, rotatedX+parentSurface->getWidth(), rotatedY+parentSurface->getHeight());
	}
	else if (rotatedX +surface->getWidth() > parentSurface->getWidth() && rotatedY+surface->getHeight() > parentSurface->getHeight())
	{
		//esquina inferior derecha
		parentSurface->draw(surface, rotatedX-parentSurface->getWidth(), rotatedY-parentSurface->getHeight());
	}
	else if (rotatedX < 0 && rotatedY+surface->getHeight() > parentSurface->getHeight())
	{
		//esquina inferior izq
		parentSurface->draw(surface, rotatedX+parentSurface->getWidth(), rotatedY-parentSurface->getHeight());
	}
	else if (rotatedX +surface->getWidth() > parentSurface->getWidth() && rotatedY < 0)
	{
		//esquina superior derecha
		parentSurface->draw(surface, rotatedX-parentSurface->getWidth(), rotatedY+parentSurface->getHeight());
	}
}

Entity* EntityView::getEntity(void)
{
	return this->entity;
}
