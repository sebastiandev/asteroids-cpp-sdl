#ifndef _SCROLLABLEPANELLAYOUT_H_
#define _SCROLLABLEPANELLAYOUT_H_

#include "layout.h"

namespace sdl
{
class ScrollablePanelLayout : public Layout
{
public:
	ScrollablePanelLayout(void);
	virtual ~ScrollablePanelLayout(void);
	virtual void applyLayout(SDLPanel*);
};
};

#endif
