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
	 * Crea un pol�gono usando como punto de referencia el Point &position con la orientacion positionLocation
	 * TopLeft => El pointPosition es utilizado como el vertice superior izq y se construir� hacia la derecha y hacia abajo
	 * Center  => El pointPosition es utilizado como el centro del pol�gono y el mismo se construir� creciendo hacia arriba, abajo, izq yd erecha
	 */

	/**
	 * El par�metro vertices especifica cuandos vertices se quieren usar para construir el c�rculo.
	 * Cuantos m�s vertices se utilicen mas redondeado ser� el pol�gono
	 */

	/**
	 * El par�metro verticalWidth especifica el ancho del rectangulo superior de la L
	 * El par�metro horizontalHeight especifica el alto del rectangulo inferior de la L
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