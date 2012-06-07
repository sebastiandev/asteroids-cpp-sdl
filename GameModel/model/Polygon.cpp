#define _USE_MATH_DEFINES

#include "Polygon.h"

#include <algorithm>
#include <iostream>
#include <math.h>

using namespace std;
using namespace model;

Polygon::Polygon(void)
{
}

Polygon::Polygon(std::vector<Point> &vertices)
{
	setVertices(vertices);
	rotatingPoint = calculateCenter();
}

Polygon::~Polygon(void)
{
	for_each(vertices.begin(), vertices.end(), [](Point*p){delete p;});
}


std::vector<Point*> Polygon::getVertices()
{
	return vertices;
}

void Polygon::addVertex(Point p)
{
	vertices.push_back(new Point(p));
	rotatingPoint = calculateCenter();
}

void Polygon::setRotatingPoint(Point point)
{
	rotatingPoint = point;
}

void Polygon::setVertices(std::vector<Point> &vertices)
{
	vector<Point>::iterator it;
	for (it=vertices.begin(); it!=vertices.end(); it++)
		this->vertices.push_back(new Point(*it));

	rotatingPoint = calculateCenter();
}

void Polygon::rotate(double angle)
{
	double realAngle = ((double)360 - angle)* M_PI/180;

	// Toma como punto de referencia para rotarel definido o sino el centro del poligono
	if (!rotatingPoint.isValid())
		rotatingPoint = calculateCenter();

	double newX = 0, newY = 0;
	vector<Point*>::iterator it;
	for (it=vertices.begin(); it!=vertices.end(); it++)
	{
		newX = cos(realAngle) * ((*it)->x() - rotatingPoint.x()) - sin(realAngle) * ((*it)->y() - rotatingPoint.y()) + rotatingPoint.x();
		newY = sin(realAngle) * ((*it)->x() - rotatingPoint.x()) + cos(realAngle) * ((*it)->y() - rotatingPoint.y()) + rotatingPoint.y();
	
		(*it)->setX(newX);
		(*it)->setY(newY);
	}
}

void Polygon::expand(double ratio)
{
	double widthIncrement  = (maxWidth () * (ratio-1)) / 2;
	double heightIncrement = (maxHeight() * (ratio-1)) / 2;
	
	doExpand(widthIncrement, heightIncrement);
}

void Polygon::expand(double xRatio, double yRatio)
{
	double widthIncrement  = (maxWidth () * (xRatio-1)) / 2;
	double heightIncrement = (maxHeight() * (yRatio-1)) / 2;

	doExpand(widthIncrement, heightIncrement);
}

void Polygon::doExpand(double xRatio, double yRatio)
{
	if (!rotatingPoint.isValid())
		rotatingPoint = calculateCenter();

	double newX = 0, newY = 0;
	vector<Point*>::iterator it;
	for (it=vertices.begin(); it!=vertices.end(); it++)
	{
		newX = (*it)->x() < rotatingPoint.x() ? (*it)->x() - xRatio :  (*it)->x() + xRatio;
		newY = (*it)->y() < rotatingPoint.y() ? (*it)->y() - yRatio :  (*it)->y() + yRatio;
	
		(*it)->setX(newX);
		(*it)->setY(newY);
	}
}

Point Polygon::calculateCenter() const
{
	int maxWidth = 0, maxHeight = 0;
	double auxDistanciaX = 0, auxDistanciaY = 0;
	double centerX = 0, centerY = 0;

	for (unsigned int i=0; i<vertices.size(); i++)
	{
		int nextVertex = 0;
		if (i+1 == vertices.size())
			nextVertex = 0;
		else
			nextVertex = i+1;

		auxDistanciaX = vertices[nextVertex]->x() - vertices[i]->x();
		auxDistanciaY = vertices[nextVertex]->y() - vertices[i]->y();
		
		// guarda la mayor distancia
		if (auxDistanciaX > maxWidth)
		{
			maxWidth = (int)auxDistanciaX;
			centerX  = vertices[i]->x();
		}

		if (auxDistanciaY > maxHeight)
		{
			maxHeight = (int)auxDistanciaY;
			centerY   = vertices[i]->y();
		}
	}

	return Point(centerX + maxWidth/2, centerY + maxHeight/2);
}

int Polygon::maxWidth() const
{
	int maxWidth = 0;
	double auxDistanciaX = 0;

	for (unsigned int i=0; i<vertices.size(); i++)
	{
		int nextVertex = 0;
		if (i+1 == vertices.size())
			nextVertex = 0;
		else
			nextVertex = i+1;

		auxDistanciaX = vertices[nextVertex]->x() - vertices[i]->x();
		
		// guarda la mayor distancia
		if (auxDistanciaX > maxWidth)
			maxWidth = (int)auxDistanciaX;
	}

	return maxWidth;
}

int Polygon::maxHeight() const
{
	int maxHeight = 0;
	double auxDistanciaY = 0;

	for (unsigned int i=0; i<vertices.size(); i++)
	{
		int nextVertex = 0;
		if (i+1 == vertices.size())
			nextVertex = 0;
		else
			nextVertex = i+1;

		auxDistanciaY = vertices[nextVertex]->y() - vertices[i]->y();
		
		if (auxDistanciaY > maxHeight)
			maxHeight = (int)auxDistanciaY;
	}

	return maxHeight;
}

bool Polygon::containsPoint(const Point &p) const
{
	unsigned int  i = 0;
    int  j = vertices.size()-1;
    bool c = false;

	for (;i<vertices.size(); i++)
	{
		// http://arxiv.org/pdf/math/9410209v1.pdf
		// PRIMER OPERANDO
		//chequea q el y del punto sea mayor al primer vertice
		//chequea q el y del punto sea mayor al ultimo vertice
		//si ambos son TRUE, el punto esta por debajo de ambos
		//caso contrario esta por arriba de ambos
		//si uno es FALSE y otro TRUE, esta en el rango de esos 2 vertices que forman ademas un vector

		// SEGUNDO OPERANDO
		//chequea q el x del punto sea menor a: 
		//    (la distancia entre el ultimo vertice(x) y el primero(x))
		//  por
		//    (la distancia entre el punto (y) y el primer vertice(y))
		//  sobre
		//    (la distancia entre el ultimo vertice (y) y el primer vertice(y))
		//  mas
		//    el primer vertice(x)

		// el negar la variable booleana es como contar la cantidad de veces q corta un lado
		// negados impartes, da siempre FALSE, negados pares da siempre TRUE 
		// => impar esta fuera (FALSE)
		// => par esta adentro (TRUE)
		if (((vertices[i]->y() > p.y()) != (vertices[j]->y() > p.y())) && 
			((p.x() < (vertices[j]->x() - vertices[i]->x()) * (p.y() - vertices[i]->y()) / (vertices[j]->y() - vertices[i]->y()) + vertices[i]->x())))
		{
			c = !c;
		}
      
		j = i;
	}

	return c;
}