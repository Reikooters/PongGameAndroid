#pragma once

class TitleText;
class Player;
class Renderer;
class InputManager;
class Timer;
class TheBall;
class ScoreToken;
class GameObject;

class Application
{
	bool showTitle;
	TitleText* titleText;
	Player* player;
	TheBall* theBall;
	Renderer* renderer;
	InputManager* inputManager;
	Timer* timer;
	int scores[2];
	ScoreToken* scoreTokenP1;
	ScoreToken* scoreTokenP2;

	GameObject** gameObjects;

public:
	// Delta time since last frame
	float dt;

	Application(int width, int height, const char* apkPath);
	~Application();

	void renderFrame();
	
	Player* getPlayer(const int playerId) const;
	Renderer* getRenderer() const;
	InputManager* getInputManager() const;
	Timer* getTimer() const;
	void score(const int playerId);
	void loadAPK(const char* apkPath);
	void loadTextures();
	void gameOver(const int winnerPlayerId);
	void startGame();
	bool playing() const;
};
