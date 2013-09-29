#include "Application.h"

//#include <jni.h>
#include <android/log.h>

//#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#include "TitleText.h"
#include "Player.h"
#include "TheBall.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Timer.h"
#include "ScoreToken.h"


#include "def.h"
#include "utils.h"

zip* APKArchive;

// Constructor
Application::Application(int width, int height, const char* apkPath)
	: player(new Player[2]), renderer(new Renderer(width, height)), inputManager(new InputManager()),
	timer(new Timer()), theBall(new TheBall()), titleText(new TitleText()), showTitle(true)
{
	loadAPK(apkPath);

	// Seed random number generator
	srand48(time(NULL));

	// Set scores
	scores[0] = 0;
	scores[1] = 0;

	// Set up players
	player[0].setPos(0.61f, 0.0f);
	player[0].setColor(1);
	player[0].playerId = 0;

	player[1].setPos(-0.61f, 0.0f);
	player[1].setColor(0);
	player[1].playerId = 1;

	// Set up game object pointers
	gameObjects = new GameObject*[24];
	gameObjects[0] = &player[0];
	gameObjects[1] = &player[1];
	gameObjects[2] = theBall;
	gameObjects[3] = titleText;

	scoreTokenP1 = new ScoreToken[10];
	scoreTokenP2 = new ScoreToken[10];

	for (int i = 0; i < 10; ++i)
	{
		scoreTokenP1[i].setPos(-0.92f, -0.85f + (0.19f * i));
		scoreTokenP2[i].setPos(0.92f, -0.85f + (0.19f * i));

		scoreTokenP1[i].setVisible(false);
		scoreTokenP2[i].setVisible(false);

		// Set up game object pointers
		gameObjects[4 + i] = &scoreTokenP1[i];
		gameObjects[14 + i] = &scoreTokenP2[i];
	}

	loadTextures();
}

Application::~Application()
{
	delete[] player;
	delete[] scoreTokenP1;
	delete[] scoreTokenP2;
	delete theBall;
	delete titleText;
	delete renderer;
	delete inputManager;
	delete timer;
}

void Application::loadAPK(const char* apkPath)
{
	LOGI("Loading APK %s", apkPath);
	APKArchive = zip_open(apkPath, 0, NULL);
	if (APKArchive == NULL)
	{
		LOGE("Error loading APK");
		//return;
	}

	//Just for debug, print APK contents
	int numFiles = zip_get_num_files(APKArchive);
	for (int i=0; i<numFiles; i++)
	{
		const char* name = zip_get_name(APKArchive, i, 0);
		if (name == NULL)
		{
			LOGE("Error reading zip file name at index %i : %s", zip_strerror(APKArchive));
			return;
		}
		LOGI("File %i : %s\n", i, name);
	}
}

void Application::renderFrame()
{
	// Clear the screen
	renderer->clear();

	// Draw purple background gradients
	renderer->drawBacklight();
	
	// Draw all game objects
	for (int i = 23; i >= 0; --i)
	{
		gameObjects[i]->update();
		gameObjects[i]->draw();
	}

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

void Application::loadTextures()
{
	for (int i = 0; i < 24; ++i)
		gameObjects[i]->loadTexture();
}
