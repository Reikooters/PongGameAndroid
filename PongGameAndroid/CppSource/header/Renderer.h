#pragma once

#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#define  LOG_TAG    "libpong"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

static const char gVertexShader[] = 
	"attribute vec4 vPosition;\n"
	"attribute vec4 vColor;\n"
	"attribute vec2 vTexCoord;\n"
	"varying vec4 fragColor;\n"
	"varying vec2 texCoord;\n"
	//"out vec2 TexCoord0;\n"
	"void main() {\n"
	"  gl_Position = vPosition;\n"
	"  fragColor = vColor;\n"
	"  texCoord = vTexCoord;\n"
	//"  TexCoord0 = vTexCoord;\n"
	//"  gl_TexCoord[0] = gl_MultiTexCoord0;\n"
	"}\n";

static const char gFragmentShader[] = 
	"uniform float useTexture;\n"
	"precision mediump float;\n"
	"varying vec4 fragColor;\n"
	"varying vec2 texCoord;\n"
	"uniform sampler2D colorMap;\n"
	"void main() {\n"
	//"  gl_FragColor = vec4(0.5, 0.0, 0.8, 1.0);\n"
	//"  gl_FragColor = fragColor;\n"
	//"  gl_FragColor = fragColor * texture2D(colorMap, TexCoord0.st);\n"
	//"  gl_FragColor = fragColor * texture2D(0, texCoord.st);\n"
	"  if (useTexture > 0.5)\n"
	"  {\n"
	"     gl_FragColor = fragColor * texture2D(colorMap, texCoord);\n"
	"  }\n"
	"  else\n"
	"  {\n"
	"     gl_FragColor = fragColor;\n"
	"  }\n"
	//"  gl_FragColor = texture2D(colorMap, texCoord.st);\n"
	//"  gl_FragColor = fragColor;\n"
	"}\n";

class Renderer
{
	GLuint loadShader(GLenum shaderType, const char* pSource);
	GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);

public:
	GLuint gProgram;
	GLuint gvPositionHandle;
	GLuint gvColorHandle;
	GLuint gvTexCoordHandle;
	GLuint gvColorMapHandle;
	GLuint gvUseTextureHandle;

	Renderer(const int width, const int height);

	void clear();
	bool setupGraphics(const int w, const int h);
	void drawArray(const void* verts, const int count, const void* colors);
	void drawArray(const void* verts, const int count, const void* colors, const void* texCoords, GLuint texId);
	void drawBacklight();
};
