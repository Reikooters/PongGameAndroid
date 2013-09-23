#include "GameObject.h"

GameObject::GameObject()
	: height(0.5f), width(0.5f), speed(1.0f), pos(Vector2(0.0f, 0.0f)), dirty(true)
{

}

GameObject::GameObject(float height, float width, float speed, Vector2 pos)
	: height(height), width(width), speed(speed), pos(pos), dirty(true)
{

}

GameObject::~GameObject()
{

}

Vector2 GameObject::getPos() const
{
	return pos;
}

void GameObject::moveTo(const float y)
{
	dest.x = pos.x;
	dest.y = y;
}

void GameObject::setPos(const float x, const float y)
{
	// Move only if necessary
	if (pos.x != x || pos.y != y)
	{
		dirty = true;

		pos.x = x;
		pos.y = y;
	}
}

void GameObject::updatePos()
{
	// todo
}

float GameObject::getHeight() const
{
	return height;
}

float GameObject::getWidth() const
{
	return width;
}
