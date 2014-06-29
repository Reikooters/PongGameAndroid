#include "Application.h"

//#include <jni.h>
#include <android/log.h>

//#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

#include "TitleText.h"
#include "TapToPlayText.h"
#include "WinnerText.h"
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
	timer(new Timer()), theBall(new TheBall()), titleText(new TitleText()), showTitle(true),
	tapToPlayText(new TapToPlayText()), winnerText(new WinnerText()), showWinner(false)
{
	loadAPK(apkPath);

	// Seed random number generator
	srand48(time(NULL));

	// Set scores
	scores[0] = 0;
	scores[1] = 0;

	// Set up players
	player[0].setColor(1);
	player[0].playerId = 0;
	player[0].reset();

	player[1].setColor(0);
	player[1].playerId = 1;
	player[1].reset();

	// Set up game object pointers
	gameObjects = new GameObject*[26];
	gameObjects[0] = &player[0];
	gameObjects[1] = &player[1];
	gameObjects[2] = theBall;
	gameObjects[3] = titleText;
	gameObjects[4] = tapToPlayText;
	gameObjects[5] = winnerText;

	winnerText->setVisible(false);

	scoreTokenP1 = new ScoreToken[10];
	scoreTokenP2 = new ScoreToken[10];

	for (int i = 0; i < 10; ++i)
	{
		scoreTokenP1[i].setPos(-0.92f, -0.85f + (0.19f * i));
		scoreTokenP1[i].playerId = 1;
		scoreTokenP1[i].setVisible(false);

		scoreTokenP2[i].setPos(0.92f, -0.85f + (0.19f * i));
		scoreTokenP2[i].playerId = 0;
		scoreTokenP2[i].setVisible(false);

		// Set up game object pointers
		gameObjects[6 + i] = &scoreTokenP1[i];
		gameObjects[16 + i] = &scoreTokenP2[i];
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

	if (showTitle)
	{
		titleText->update();
		titleText->draw();
		tapToPlayText->update();
		tapToPlayText->draw();
	}
	else if (showWinner)
	{
		winnerText->update();
		winnerText->draw();
	}
	else
	{
		// Draw all game objects
		for (int i = 25; i >= 0; --i)
		{
			gameObjects[i]->update();
			gameObjects[i]->draw();
		}
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

	if (scores[playerId] <= 4)
	{
		if (playerId == 0)
			scoreTokenP1[ scores[playerId] - 1 ].setVisible(true);
		else if (playerId == 1)
			scoreTokenP2[ scores[playerId] - 1 ].setVisible(true);
	}
	else
	{
		// The player who scored won the game
		gameOver(playerId);
	}
}

void Application::loadTextures()
{
	for (int i = 0; i < 26; ++i)
		gameObjects[i]->loadTexture();
}

void Application::gameOver(const int winnerPlayerId)
{
	theBall->reset();
	player[0].reset();
	player[1].reset();

	scores[0] = 0;
	scores[1] = 0;

	for (int i = 0; i < 10; ++i)
	{
		scoreTokenP1[i].setVisible(false);
		scoreTokenP2[i].setVisible(false);
	}

	player[0].setVisible(false);
	player[1].setVisible(false);
	theBall->setVisible(false);

	winnerText->playerId = winnerPlayerId;
	winnerText->setVisible(true);
	winnerText->reset();
	showWinner = true;

	//showTitle = true;
	//titleText->setVisible(true);
	//tapToPlayText->setVisible(true);
}

void Application::startGame()
{
	showTitle = false;
	showWinner = false;
	titleText->setVisible(false);
	tapToPlayText->setVisible(false);
	winnerText->setVisible(false);

	player[0].setVisible(true);
	player[1].setVisible(true);
	theBall->setVisible(true);
}

void Application::showTitleScreen()
{
	showTitle = true;
	winnerText->setVisible(false);
	titleText->setVisible(true);
	tapToPlayText->setVisible(true);
	showWinner = false;
}

bool Application::playing() const
{
	if (!showTitle && !showWinner)
		return true;
	else
		return false;
}
