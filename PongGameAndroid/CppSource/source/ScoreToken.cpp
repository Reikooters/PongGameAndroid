#include "ScoreToken.h"

#include "Application.h"
#include "Renderer.h"
#include "Timer.h"
#include "Vector2.h"

// Contains loadTextureFromPNG()
#include "utils.h"

extern Application* app;

// Constructor. Iniitialises variables.
ScoreToken::ScoreToken()
	: GameObject(0.247f, 0.247f * (1080.0f / 1920.0f), // height and width of score token - viewing phone horizontally
	0.0f, // speed
	Vector2()) // position
{
	verts = new GLfloat[12]; // 6 points, 2 dimensional coords
	colors = new GLfloat[24]; // 6 points, 4 floats make up each color
	texCoords = new GLfloat[12]; // 6 points, 2 dimensional coords
}

ScoreToken::~ScoreToken()
{
	delete[] verts;
	delete[] colors;
	delete[] texCoords;
}

// Draws the score token on the screen.
void ScoreToken::draw()
{
	// Draw only if object is visible
	if (!visible) return;

	app->getRenderer()->drawArray(verts, 6, colors, texCoords, texture);
}

// Sets the position of the score token. Sets dirty if new position is not the current one.
void ScoreToken::setPos(const float x, const float y)
{
	GameObject::setPos(x, y);
}

// Recalculates vertices that make up triangles to create the score token
void ScoreToken::recalcVerts()
{
	// Recalc only if dirty
	if (!dirty)
		return;

	// Calculate score token corner coordinates
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

// Updates Score Token status (such as position)
void ScoreToken::update()
{
	// Update ball position
	updatePos();

	// Recalculate verts if needed
	if (dirty)
		recalcVerts();
}

// Moves score token toward destination position
void ScoreToken::updatePos()
{
	
}

// Loads texture for the ball from .apk
void ScoreToken::loadTexture()
{
	// Don't load again if already loaded
	if (texture)
		return;

	// Load texture from file
	int width, height;
	if (playerId == 0)
		texture = loadTextureFromPNG("assets/scoretoken0.png", width, height);
	else
		texture = loadTextureFromPNG("assets/scoretoken1.png", width, height);

	// Set up texture coords
	texCoords[0] = 0.0f;	texCoords[1] = 1.0f;
	texCoords[2] = 1.0f;	texCoords[3] = 1.0f;
	texCoords[4] = 1.0f;	texCoords[5] = 0.0f;
	texCoords[6] = 1.0f;	texCoords[7] = 0.0f;
	texCoords[8] = 0.0f;	texCoords[9] = 0.0f;
	texCoords[10] = 0.0f;	texCoords[11] = 1.0f;

	// Set up vertex colors
	for (int i = 0; i < 6; ++i)
	{
		colors[(i*4)+0] = 1.0f;
		colors[(i*4)+1] = 1.0f;
		colors[(i*4)+2] = 1.0f;
		colors[(i*4)+3] = 1.0f;
	}
}
