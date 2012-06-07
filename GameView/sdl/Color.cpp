#include "Color.h"

Color::Color(int r, int g, int b) : red(r), green(g), blue(b), alpha(0)
{
}

Color::Color(int r, int g, int b, int a) : red(r), green(g), blue(b), alpha(a)
{
}

Color::~Color(void)
{
}

int Color::getRed(void)
{
	return red;
}

int Color::getGreen(void)
{
	return green;
}

int Color::getBlue(void)
{
	return blue;
}

int Color::getAlpha(void)
{
	return alpha;
}
