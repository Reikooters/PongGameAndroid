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
	"varying vec4 fragColor;\n"
	"void main() {\n"
	"  gl_Position = vPosition;\n"
	"  fragColor = vColor;\n"
	"}\n";

static const char gFragmentShader[] = 
	"precision mediump float;\n"
	"varying vec4 fragColor;\n"
	"void main() {\n"
	//"  gl_FragColor = vec4(0.5, 0.0, 0.8, 1.0);\n"
	"  gl_FragColor = fragColor;\n"
	"}\n";

class Renderer
{
	GLuint loadShader(GLenum shaderType, const char* pSource);
	GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);

public:
	GLuint gProgram;
	GLuint gvPositionHandle;
	GLuint gvColorHandle;

	Renderer(const int width, const int height);

	void clear();
	bool setupGraphics(const int w, const int h);
	void drawArray(const void* verts, const int count, const float* color);
	void drawArray(const void* verts, const int count, const float colorR, const float colorG, const float colorB, const float colorA);
	void drawBacklight();
};
