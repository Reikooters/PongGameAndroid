#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class Player;

class Application
{
	Player* player;

	GLuint loadShader(GLenum shaderType, const char* pSource);
	GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);

public:
	GLuint gProgram;
	GLuint gvPositionHandle;

	Application(int width, int height);
	~Application();

	void renderFrame();
	bool setupGraphics(int w, int h);
};
