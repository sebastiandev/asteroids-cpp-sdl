#ifndef _LAYOUT_H_
#define _LAYOUT_H_

#include "SDLPanel.h"

namespace sdl
{
class SDLPanel;
class Layout
{
public:
	Layout(void);
	virtual ~Layout(void);
	virtual void applyLayout(SDLPanel*)=0;
};
};

#endif
