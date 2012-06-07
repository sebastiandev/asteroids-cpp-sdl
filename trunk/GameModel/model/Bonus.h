#ifndef _BONUS_H_
#define _BONUS_H_

#include "Entity.h"

namespace model
{
class Bonus : public Entity
{
public:
	Bonus(void);
	virtual ~Bonus(void);
	
	string getImagePath(void);
	void   setImagePath(string path);
	void   setStartTime(double);
	double getStartTime();
	void   setCode(char);
	char   getCode();
	void   updatePositions(double);

private:
	string imagePath;
	double startTime;
	char   code;
};
};

#endif
