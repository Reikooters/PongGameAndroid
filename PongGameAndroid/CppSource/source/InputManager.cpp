#include "InputManager.h"

#include "Application.h"
#include "Player.h"

extern Application* app;

InputManager::InputManager()
{

}

void InputManager::addPointer(const int pointerId, const float x, const float y)
{
	if (y < 630.0f)
	{
		pointer[0] = pointerId; // Set player 1's pointer id
		app->getPlayer(0)->moveTo(((x / 1080.0f) - 0.5f) * 2.0f);
	}
	else if (y > 1250.0f)
	{
		pointer[1] = pointerId; // Set player 2's pointer id
		app->getPlayer(1)->moveTo(((x / 1080.0f) - 0.5f) * 2.0f);
	}
}

void InputManager::movePointer(const int pointerId, const float x, const float y)
{
	if (pointer[0] == pointerId)
	{
		app->getPlayer(0)->moveTo(((x / 1080.0f) - 0.5f) * 2.0f);
	}
	else if (pointer[1] == pointerId)
	{
		app->getPlayer(1)->moveTo(((x / 1080.0f) - 0.5f) * 2.0f);
	}
}

void InputManager::removePointer(const int pointerId)
{
	if (pointer[0] == pointerId)
		pointer[0] = -1;
	else if (pointer[1] == pointerId)
		pointer[1] = -1;
}
