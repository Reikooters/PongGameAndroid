class Player;
class Renderer;

class Application
{
	Player* player;

public:
	Renderer* renderer;

	Application(int width, int height);
	~Application();

	void renderFrame();
	void touched(int pointerId);
	void untouched(int pointerId);
};
