#include "Application.h"

//#include <jni.h>
#include <android/log.h>

//#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#include "Player.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Timer.h"

// Constructor
Application::Application(int width, int height)
	: player(new Player[2]), renderer(new Renderer(width, height)), inputManager(new InputManager()),
	timer(new Timer())
{
	player[0].setPos(0.61f, 0.0f);
	player[0].setColor(1);

	player[1].setPos(-0.61f, 0.0f);
	player[1].setColor(0);
}

Application::~Application()
{
	delete[] player;
	delete renderer;
	delete inputManager;
	delete timer;
}

void Application::renderFrame()
{
	// Clear the screen
	renderer->clear();

	renderer->drawBacklight();

	// Update and draw Player 1
	player[0].update();
	player[0].draw();

	// Update and draw Player 2
	player[1].update();
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

	timer->tick();
}

Player* Application::getPlayer(const int playerId) const
{
	if (playerId == 0 || playerId == 1)
		return &player[playerId];
}

Renderer* Application::getRenderer() const
{
	return renderer;
}

InputManager* Application::getInputManager() const
{
	return inputManager;
}

Timer* Application::getTimer() const
{
	return timer;
}
