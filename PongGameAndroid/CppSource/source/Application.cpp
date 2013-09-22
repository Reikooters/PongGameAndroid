#include "Application.h"

//#include <jni.h>
#include <android/log.h>

//#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#include "Player.h"
#include "Renderer.h"
#include "InputManager.h"

// Constructor
Application::Application(int width, int height)
{
	player = new Player[2];
	renderer = new Renderer(width, height);
	inputManager = new InputManager();

	player[0].setPos(0.61f, 0.0f);
	player[1].setPos(-0.61f, 0.0f);
}

Application::~Application()
{
	delete[] player;
	delete renderer;
	delete inputManager;
}

// Renders one frame
void Application::renderFrame()
{
	glClearColor(0.25f, 0.07f, 0.25f, 1.0f);
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	player[0].draw();
	player[1].draw();

	/*
	const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
        0.5f, -0.5f };

	glUseProgram(gProgram);
	glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    glEnableVertexAttribArray(gvPositionHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
	*/

	/*
	static float grey;
    grey += 0.01f;
    if (grey > 1.0f) {
        grey = 0.0f;
    }
    glClearColor(grey, grey, grey, 1.0f);
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

	const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
        0.5f, -0.5f };

    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");
	*/
}

void Application::touched(int pointerId)
{
	if (pointerId == 0 || pointerId == 1)
		player[pointerId].setPos( player[pointerId].getPos().x , 0.5f);
}

void Application::untouched(int pointerId)
{
	if (pointerId == 0 || pointerId == 1)
		player[pointerId].setPos( player[pointerId].getPos().x , 0.0f);
}

Player* Application::getPlayer(const int playerId)
{
	if (playerId == 0 || playerId == 1)
		return &player[playerId];
}

Renderer* Application::getRenderer()
{
	return renderer;
}

InputManager* Application::getInputManager()
{
	return inputManager;
}