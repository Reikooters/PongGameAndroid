#include "ScoreToken.h"

#include "Application.h"
#include "Renderer.h"
#include "Timer.h"
#include "Vector2.h"

extern Application* app;

// Constructor. Iniitialises variables.
ScoreToken::ScoreToken()
	: GameObject(0.047f, 0.047f * (1080.0f / 1920.0f), // height and width of ball - viewing phone horizontally
	0.0f, // speed
	Vector2()) // position
{
	verts = new GLfloat[12]; // 6 points, 2 dimensional coords
	colors = new GLfloat[24]; // 6 points, 4 floats make up each color

	for (int i = 0; i < 6; ++i)
	{
		colors[(i*4)+0] = 1.0f;
		colors[(i*4)+1] = 1.0f;
		colors[(i*4)+2] = 1.0f;
		colors[(i*4)+3] = 0.7f;
	}
}

ScoreToken::~ScoreToken()
{
	delete[] verts;
	delete[] colors;
}

// Draws the score token on the screen.
void ScoreToken::draw()
{
	// Draw only if object is visible
	if (!visible) return;

	app->getRenderer()->drawArray(verts, 6, colors);
}

// Sets the position of the score token. Sets dirty if new position is not the current one.
void ScoreToken::setPos(const float x, const float y)
{
	GameObject::setPos(x, y);
}

// Recalculates vertices that make up triangles to create the paddle
void ScoreToken::recalcVerts()
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
void ScoreToken::update()
{
	// Update ball position
	updatePos();

	// Recalculate verts if needed
	if (dirty)
		recalcVerts();
}

// Moves player toward destination position
void ScoreToken::updatePos()
{
	
}
