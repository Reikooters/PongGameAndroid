#include "InputManager.h"

#include "Application.h"
#include "Player.h"

extern Application* app;

InputManager::InputManager()
{

}

void InputManager::addPointer(const int pointerId, const float x, const float y)
{
	if (y < 900.0f) app->getPlayer(0)->moveTo(((x / 1080.0f) - 0.5f) * 2.0f);
	else if (y > 980.0f) app->getPlayer(1)->moveTo(((x / 1080.0f) - 0.5f) * 2.0f);
}

void InputManager::movePointer(const int pointerId, const float x, const float y)
{
	if (y < 900.0f) app->getPlayer(0)->moveTo(((x / 1080.0f) - 0.5f) * 2.0f);
	else if (y > 980.0f) app->getPlayer(1)->moveTo(((x / 1080.0f) - 0.5f) * 2.0f);
}

void InputManager::removePointer(const int pointerId)
{
	
}
