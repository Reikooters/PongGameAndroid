#include "Player.h"

#include <algorithm>

#include "Application.h"
#include "Renderer.h"
#include "Timer.h"

extern Application* app;

// Constructor. Iniitialises variables.
Player::Player()
	: height(0.45f), width(0.062f), // height and width of paddle - viewing phone horizontally
	speed(0.0009f), dirty(true), color(0)
{
	verts = new GLfloat[12]; // 6 points, 2 dimensional coords
}

Player::~Player()
{
	delete[] verts;
}

// Draws the player on the screen.
void Player::draw()
{
	// Make player blink orange
	static float grey;
    grey += 0.003f;
    if (grey > 1.0f) grey = 0.8f;
	else if (grey < 0.8f) grey = 0.8f;

	if (color == 0)
		app->getRenderer()->drawArray(verts, 6, grey, grey * 0.7f, 0.0f, 1.0f);
	else
		app->getRenderer()->drawArray(verts, 6, 0.4f, grey * 0.9f, grey, 1.0f);
}

// Sets the position of the player. Sets dirty if new position is not the current one.
void Player::setPos(const float x, const float y)
{
	// Move only if necessary
	if (pos.x != x || pos.y != y)
	{
		dirty = true;

		pos.x = x;
		pos.y = y;
	}

	// Clamp paddle position
	if (pos.y < -0.75f) pos.y = -0.75f;
	else if (pos.y > 0.75f) pos.y = 0.75f;
}

// Recalculates vertices that make up triangles to create the paddle
void Player::recalcVerts()
{
	// Recalc only if dirty
	if (!dirty)
		return;

	// Calculate paddle corner coordinates
	float x1 = pos.x - (width / 2);
	float x2 = pos.x + (width / 2);
	float y1 = pos.y - (height / 2);
	float y2 = pos.y + (height / 2);

	// Lower right triangle
	verts[0] = y1;
	verts[1] = x1;

	verts[2] = y2;
	verts[3] = x1;

	verts[4] = y2;
	verts[5] = x2;

	// Upper left triangle
	verts[6] = y2;
	verts[7] = x2;

	verts[8] = y1;
	verts[9] = x2;

	verts[10] = y1;
	verts[11] = x1;

	// Remove dirty flag
	dirty = false;
}

// Returns the current position of the player.
Vector2 Player::getPos()
{
	return pos;
}

// Sets destination position of the paddle
void Player::moveTo(float y)
{
	dest.x = pos.x;
	dest.y = y;
}

// Updates Player status (such as position)
void Player::update()
{
	// Update player position
	updatePos();

	// Recalculate verts if needed
	if (dirty)
		recalcVerts();
}

// Moves player toward destination position
void Player::updatePos()
{
	if (pos.y == dest.y)
		return;

	float diff, newY, dt;

	dt = app->getTimer()->getDeltaTime();

	if (pos.y > dest.y)
	{
		diff = pos.y - dest.y;
		setPos(pos.x, pos.y - (diff / (speed * dt)));
	}
	else
	{
		diff = dest.y - pos.y;
		setPos(pos.x, pos.y + (diff / (speed * dt)));
	}
}

void Player::setColor(int color)
{
	this->color = color;
}
