#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
	Color(int, int, int);
	Color(int, int, int, int);
	virtual ~Color(void);
	int getRed(void);
	int getGreen(void);
	int getBlue(void);
	int getAlpha(void);
private:
	int red;
	int green;
	int blue;
	int alpha;
};

#endif
