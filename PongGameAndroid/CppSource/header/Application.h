#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

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
};
