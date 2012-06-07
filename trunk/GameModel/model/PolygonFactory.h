#ifndef POLYGONFACTORY_H
#define POLYGONFACTORY_H

#include "Polygon.h"

namespace model
{
class Point;

class PolygonFactory
{
public:

	~PolygonFactory(){}

	typedef enum PolygonType   { PF_L, PF_Square, PF_Circle, PF_Rectangle, PF_Triangle};
	typedef enum PolygonOrigin { PF_Center, PF_TopLeft, PF_TopRight, PF_BottomLeft, PF_BottomRight};

	static PolygonFactory& instance();

	/**
	 * Crea un polígono usando como punto de referencia el Point &position con la orientacion positionLocation
	 * TopLeft => El pointPosition es utilizado como el vertice superior izq y se construirá hacia la derecha y hacia abajo
	 * Center  => El pointPosition es utilizado como el centro del polígono y el mismo se construirá creciendo hacia arriba, abajo, izq yd erecha
	 */

	/**
	 * El parámetro vertices especifica cuandos vertices se quieren usar para construir el círculo.
	 * Cuantos más vertices se utilicen mas redondeado será el polígono
	 */

	/**
	 * El parámetro verticalWidth especifica el ancho del rectangulo superior de la L
	 * El parámetro horizontalHeight especifica el alto del rectangulo inferior de la L
	 */

	Polygon* createSquare   (const Point &position, short positionLocation=PF_TopLeft, int size=50);
	Polygon* createRectangle(const Point &position, short positionLocation=PF_TopLeft, int width=50, int height=100);
	Polygon* createTriangle (const Point &position, short positionLocation=PF_TopLeft, int width=100, int height=50);
	Polygon* createCircle   (const Point &position, short positionLocation=PF_TopLeft, int vertices=8);
	Polygon* createL        (const Point &position, short positionLocation=PF_TopLeft, int width=100, int height=100, int verticalWidth=20, int horizontalHeight=20);

protected:

	PolygonFactory(){}

};
};
#endif