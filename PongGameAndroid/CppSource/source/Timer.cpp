#include "Timer.h"

Timer::Timer()
	: deltaTime(0), lastTime(clock())
{
	
}

float Timer::getDeltaTime() const
{
	return deltaTime;
}

void Timer::tick()
{
	clock_t now = clock();
	deltaTime = now - lastTime;
	lastTime = now;
}
