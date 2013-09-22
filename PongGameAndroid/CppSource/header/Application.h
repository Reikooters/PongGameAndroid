class Player;
class Renderer;
class InputManager;

class Application
{
	Player* player;
	Renderer* renderer;
	InputManager* inputManager;

public:
	

	Application(int width, int height);
	~Application();

	void renderFrame();
	void touched(int pointerId);
	void untouched(int pointerId);
	
	Player* getPlayer(const int playerId);
	Renderer* getRenderer();
	InputManager* getInputManager();
};
