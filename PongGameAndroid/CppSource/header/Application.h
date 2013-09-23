#pragma once

class Player;
class Renderer;
class InputManager;
class Timer;
class TheBall;

class Application
{
	Player* player;
	TheBall* theBall;
	Renderer* renderer;
	InputManager* inputManager;
	Timer* timer;
	int scores[2];

public:
	// Delta time since last frame
	float dt;

	Application(int width, int height);
	~Application();

	void renderFrame();
	
	Player* getPlayer(const int playerId) const;
	Renderer* getRenderer() const;
	InputManager* getInputManager() const;
	Timer* getTimer() const;
};
