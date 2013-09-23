#include "Player.h"

#include "Application.h"
#include "Renderer.h"
#include "Timer.h"

extern Application* app;

// Constructor. Iniitialises variables.
Player::Player()
	: GameObject(0.45f, 0.062f, // height and width of paddle - viewing phone horizontally
	0.0009f, // speed
	Vector2()), // position
	color(0), colorStep(0.8f) // color
{
	verts = new GLfloat[12]; // 6 points, 2 dimensional coords
	colors = new GLfloat[24]; // 6 points, 4 floats make up each color
}

Player::~Player()
{
	delete[] verts;
	delete[] colors;
}

// Draws the player on the screen.
void Player::draw()
{
	if (color == 0)
		app->getRenderer()->drawArray(verts, 6, colors);
	else
		app->getRenderer()->drawArray(verts, 6, colors);
}

// Sets the position of the player. Sets dirty if new position is not the current one.
void Player::setPos(const float x, const float y)
{
	if (x != pos.x || y != pos.y)
		dirty = true;

	GameObject::setPos(x, y);

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

// Updates Player status (such as position)
void Player::update()
{
	// Update player position
	updatePos();

	// Update player color
	updateColor();

	// Recalculate verts if needed
	if (dirty)
		recalcVerts();
}

// Moves player toward destination position
void Player::updatePos()
{
	// todo: fix this code and put it in GameObject::updatePos() instead.
	if (pos.y == dest.y)
		return;

	float diff, newY;

	if (pos.y > dest.y)
	{
		diff = pos.y - dest.y;
		setPos(pos.x, pos.y - (diff / (speed * app->dt)));
	}
	else
	{
		diff = dest.y - pos.y;
		setPos(pos.x, pos.y + (diff / (speed * app->dt)));
	}
}

// Sets the paddle color. 0 = Pink, 1 = Blue.
void Player::setColor(int color)
{
	if (color != 0 && color != 1)
		return;

	this->color = color;
}

// Animates the player's color
void Player::updateColor()
{
	// Make player color blink
    colorStep += 0.003f;
    if (colorStep > 1.0f) colorStep = 0.8f;
	else if (colorStep < 0.8f) colorStep = 0.8f;

	if (color == 0)
	{
		for (int i = 0; i < 6; ++i)
		{
			colors[(i*4)+0] = colorStep;
			colors[(i*4)+1] = colorStep * 0.5f;
			colors[(i*4)+2] = colorStep;
			colors[(i*4)+3] = 1.0f;
		}
	}
	else if (color == 1)
	{
		for (int i = 0; i < 6; ++i)
		{
			colors[(i*4)+0] = 0.4f;
			colors[(i*4)+1] = colorStep * 0.9f;
			colors[(i*4)+2] = colorStep;
			colors[(i*4)+3] = 1.0f;
		}
	}
}