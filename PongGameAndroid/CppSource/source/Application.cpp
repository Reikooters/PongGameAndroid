#include "Application.h"

//#include <jni.h>
#include <android/log.h>

//#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#include "Player.h"
#include "TheBall.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Timer.h"
#include "ScoreToken.h"

// Constructor
Application::Application(int width, int height)
	: player(new Player[2]), renderer(new Renderer(width, height)), inputManager(new InputManager()),
	timer(new Timer()), theBall(new TheBall())
{
	scores[0] = 0;
	scores[1] = 0;

	player[0].setPos(0.61f, 0.0f);
	player[0].setColor(1);

	player[1].setPos(-0.61f, 0.0f);
	player[1].setColor(0);

	scoreTokenP1 = new ScoreToken[10];
	scoreTokenP2 = new ScoreToken[10];

	for (int i = 0; i < 10; ++i)
	{
		scoreTokenP1[i].setPos(-0.92f, -0.85f + (0.19f * i));
		scoreTokenP2[i].setPos(0.92f, -0.85f + (0.19f * i));

		scoreTokenP1[i].setVisible(false);
		scoreTokenP2[i].setVisible(false);
	}
}

Application::~Application()
{
	delete[] player;
	delete[] scoreTokenP1;
	delete[] scoreTokenP2;
	delete theBall;
	delete renderer;
	delete inputManager;
	delete timer;
}

void Application::renderFrame()
{
	// Clear the screen
	renderer->clear();

	// Draw purple background gradients
	renderer->drawBacklight();

	// Update and draw Player 1
	player[0].update();
	player[0].draw();

	// Update and draw Player 2
	player[1].update();
	player[1].draw();

	// Update and draw The Ball
	theBall->update();
	theBall->draw();
	
	for (int i = 0; i < 10; ++i)
	{
		scoreTokenP1[i].update();
		scoreTokenP1[i].draw();

		scoreTokenP2[i].update();
		scoreTokenP2[i].draw();
	}

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
	dt = timer->getDeltaTime();
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

void Application::score(const int playerId)
{
	if (playerId != 0 && playerId != 1)
		return;

	scores[playerId] += 1;
	theBall->reset();

	if (scores[playerId] <= 10)
	{
		if (playerId == 0)
			scoreTokenP1[ scores[playerId] - 1 ].setVisible(true);
		else if (playerId == 1)
			scoreTokenP2[ scores[playerId] - 1 ].setVisible(true);
	}
}
