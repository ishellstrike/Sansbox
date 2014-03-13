#ifndef FPSCounter_h__
#define FPSCounter_h__

#include <list>
#include "GameTimer.h"

class FPSCounter
{
private:
	//std::list<double> fpsStack;

	int fps, fpsC;
	double fpsTime;

public:
	FPSCounter(void);
	~FPSCounter(void);

	void Update(GameTimer gt);

	unsigned int GetCount();

};


#endif // FPSCounter_h__