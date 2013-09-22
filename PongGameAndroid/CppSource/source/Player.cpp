#include "Player.h"

#include "Application.h"
#include "Renderer.h"

extern Application* app;

// Constructor
Player::Player()
	: height(0.45f), width(0.062f) // height and width of paddle - viewing phone horizontally
{
	verts = new GLfloat[12];
}

// Draws the player on the screen.
void Player::draw()
{
	app->renderer->drawArray(verts, 6, 1.0f, 0.7f, 0.0f, 1.0f);
}

void Player::setPos(const float x, const float y)
{
	pos.x = x;
	pos.y = y;

	recalcVerts();
}

void Player::recalcVerts()
{
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
}
