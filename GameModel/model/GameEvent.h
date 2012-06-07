#ifndef _GAMEEVENT_H_
#define _GAMEEVENT_H_

#include <string>

using namespace std;

namespace model
{
class GameEvent
{
public:
	GameEvent(void);
	virtual ~GameEvent(void);

	typedef enum GameEventType
	{
		ACCELERATE,
		ACCELERATE_LEFT,
		ACCELERATE_RIGHT,
		ROTATE_LEFT,
		ROTATE_RIGHT,
		SHOOT,
		STOP_ACCELERATE,
		STOP_ROTATION,
		QUIT
	};

	virtual void setClientId(int)=0;
	virtual int getType(void)=0;
	virtual int getClientId(void)=0;
	virtual string getClientIdStr(void)=0;
};
};

#endif
