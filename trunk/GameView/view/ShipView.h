#ifndef _SHIPVIEW_H_
#define _SHIPVIEW_H_

#include "EntityView.h"
#include "..\..\GameModel\model\Ship.h"

namespace view
{
class ShipView : public EntityView
{
public:

	ShipView (Entity *entity, SDLSurface* parentSurface, string accelerateImagePath);
	ShipView (Entity *entity, SDLSurface* parentSurface, int width, int height, string accelerateImagePath);
	~ShipView(void);

	void   setAcceleratingImage(string imagePath);
	string getAcceleratingImage();

	void   paint(void);

protected:

	string acceleratingImage;
	SDLSurface *accelerated;
	SDLSurface *temp;
};
};
#endif