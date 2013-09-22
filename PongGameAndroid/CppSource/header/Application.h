#pragma once

class Player;
class Renderer;
class InputManager;
class Timer;

class Application
{
	Player* player;
	Renderer* renderer;
	InputManager* inputManager;
	Timer* timer;

public:
	
	Application(int width, int height);
	~Application();

	void renderFrame();
	
	Player* getPlayer(const int playerId) const;
	Renderer* getRenderer() const;
	InputManager* getInputManager() const;
	Timer* getTimer() const;
};
