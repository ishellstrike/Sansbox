#include "FPSCounter.h"

#include <glfw3.h>



FPSCounter::FPSCounter(void)
{
	fpsTime = 0;
	fpsC = 0;
}


FPSCounter::~FPSCounter(void)
{
}

void FPSCounter::Update(GameTimer gt)
{
	fpsTime += gt.elapsed;
	fpsC++;
	if(fpsTime > 1.0){
		fpsTime -= 1.0;
		fps = fpsC;
		fpsC = 0;
	}
}

unsigned int FPSCounter::GetCount()
{
	return fps;
}
