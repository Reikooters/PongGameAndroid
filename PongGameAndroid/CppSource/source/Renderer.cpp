#include "Renderer.h"

#include <stdlib.h>

Renderer::Renderer(const int width, const int height)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	setupGraphics(width, height);
}

GLuint Renderer::loadShader(GLenum shaderType, const char* pSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint Renderer::createProgram(const char* pVertexSource, const char* pFragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

bool Renderer::setupGraphics(const int w, const int h)
{
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return false;
    }
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
	gvColorHandle = glGetAttribLocation(gProgram, "vColor");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
            gvPositionHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    return true;
}

void Renderer::drawArray(const void* verts, const int count, const void* colors)
{
	glUseProgram(gProgram);

	// Set drawing color
	//glUniform4f(
	//	glGetUniformLocation(gProgram, "color"),
	//	colorR, colorG, colorB, colorA
	//);

	glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, verts);
	glVertexAttribPointer(gvColorHandle, 4, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(gvPositionHandle);
	glEnableVertexAttribArray(gvColorHandle);
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::drawBacklight()
{
	glUseProgram(gProgram);

	GLfloat square[] = { -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 0.2f,  // Top player, upper left triangle
						 1.0f, 1.0f, 1.0f, 0.2f, -1.0f, 0.2f,   // Top player, lower right triange
						 -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, -0.2f, // Bottom player, lower left triangle
						 1.0f, -1.0f, 1.0f, -0.2f, -1.0f, -0.2f }; // Bottom player, upper right triangle
	
	GLfloat colors[] = { 0.5f, 0.0f, 0.8f, 0.7f,
						 0.5f, 0.0f, 0.8f, 0.7f,
						 0.5f, 0.0f, 0.8f, 0.0f,
						 0.5f, 0.0f, 0.8f, 0.7f,
						 0.5f, 0.0f, 0.8f, 0.0f,
						 0.5f, 0.0f, 0.8f, 0.0f, // end of first square
						 0.5f, 0.0f, 0.8f, 0.7f,
						 0.5f, 0.0f, 0.8f, 0.7f,
						 0.5f, 0.0f, 0.8f, 0.0f,
						 0.5f, 0.0f, 0.8f, 0.7f,
						 0.5f, 0.0f, 0.8f, 0.0f,
						 0.5f, 0.0f, 0.8f, 0.0f }; // end of second square

	glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, square);
	glVertexAttribPointer(gvColorHandle, 4, GL_FLOAT, GL_FALSE, 0, colors);
    glEnableVertexAttribArray(gvPositionHandle);
	glEnableVertexAttribArray(gvColorHandle);
	glDrawArrays(GL_TRIANGLES, 0, 12);
}

void Renderer::clear()
{
	glClearColor(0.25f, 0.07f, 0.25f, 1.0f);
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}
