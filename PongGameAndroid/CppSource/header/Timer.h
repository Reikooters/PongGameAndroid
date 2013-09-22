#pragma once

#include <ctime>

class Timer
{
	clock_t now;
	clock_t lastTime;
	float deltaTime;

public:
	Timer();

	void tick();
	float getDeltaTime() const;
};
