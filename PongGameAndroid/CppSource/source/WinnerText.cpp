#include "WinnerText.h"

#include "Application.h"
#include "Renderer.h"
#include "Timer.h"
#include "Vector2.h"

// Contains loadTextureFromPNG()
#include "utils.h"

extern Application* app;

// Constructor. Iniitialises variables.
WinnerText::WinnerText()
	//: GameObject(0.9f, 0.047f * (1080.0f / 1920.0f), // height and width - viewing phone horizontally
	: GameObject(1.2f, 1.8f, // height and width - viewing phone horizontally
	0.000002f, // speed
	Vector2()), // position
	vertCount(6),
	colorDir(true)
{
	verts = new GLfloat[vertCount * 2]; // 2 dimensional coords
	colors = new GLfloat[vertCount * 4]; // 4 floats make up each color
	texCoords = new GLfloat[vertCount * 2]; // 2 dimensional coords
}

WinnerText::~WinnerText()
{
	delete[] verts;
	delete[] colors;
	delete[] texCoords;
}

// Draws the text on the screen.
void WinnerText::draw()
{
	// Draw only if object is visible
	if (!visible) return;

	if (playerId == 0)
		app->getRenderer()->drawArray(verts, vertCount, colors, texCoords, texture0);
	else
		app->getRenderer()->drawArray(verts, vertCount, colors, texCoords, texture1);
}

// Sets the position of the text. Sets dirty if new position is not the current one.
void WinnerText::setPos(const float x, const float y)
{
	GameObject::setPos(x, y);
}

// Recalculates vertices that make up triangles to create the text
void WinnerText::recalcVerts()
{
	// Recalc only if dirty
	if (!dirty)
		return;

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

// Updates Text status (such as position)
void WinnerText::update()
{
	// Update text position
	updatePos();

	// Update text color
	updateColor();

	// Recalculate verts if needed
	if (dirty)
		recalcVerts();
}

// Moves text toward destination position
void WinnerText::updatePos()
{
	if (!app->showWinner)
		return;

	//speed = 0.0000028f;

	if (playerId == 1)
	{
		setPos(pos.x - (speed * app->dt), pos.y);
		if (pos.x < dest.x)
			app->showTitleScreen();
	}
	else
	{
		setPos(pos.x + (speed * app->dt), pos.y);
		if (pos.x > dest.x)
			app->showTitleScreen();
	}

	dirty = true;

	return;

	// todo: fix this code and put it in GameObject::updatePos() instead.
	if (pos.x == dest.x)
	{
		if (app->showWinner)
			app->showTitleScreen();
		return;
	}

	float diff, newX;

	if (playerId == 1)
	{
		if (pos.x > -0.8f && pos.x < -0.2f)
		{
			speed -= 0.003f;
		}
		else if (pos.x > -0.2f && pos.x < 0.7f)
		{
			speed += 0.0004f;
		}

		if (pos.x > dest.x)
		{
			diff = pos.x - dest.x;

			if (diff < 0.0f)
				diff = -diff;
			setPos(pos.x - (diff / (speed * app->dt)), pos.y);
		}
		else
		{
			app->showTitleScreen();
		}
	}
	else
	{
		if (pos.x < 0.8f && pos.x > 0.2f)
			speed -= 0.003f;
		else if (pos.x < 0.2f && pos.x > -0.7f)
			speed += 0.0004f;

		if (pos.x < dest.x)
		{
			diff = dest.x - pos.x;
			if (diff < 0.0f)
				diff = -diff;
			setPos(pos.x + (diff / (speed * app->dt)), pos.y);
		}
		else
		{
			app->showTitleScreen();
		}
	}
}

// Animates the text's color
void WinnerText::updateColor()
{
	return; // disabled for now

	if (colorDir)
		colorStep += 0.005f;
	else
		colorStep -= 0.005f;

	if (colorStep > 0.3f) { colorStep = 0.3f; colorDir = !colorDir; }
	else if (colorStep < 0.0f) { colorStep = 0.0f; colorDir = !colorDir; }

	for (int i = 0; i < vertCount; ++i)
	{
		colors[(i*4)+0] = 1.0f;
		colors[(i*4)+1] = 1.0f;
		colors[(i*4)+2] = 1.0f;
		colors[(i*4)+3] = 1.0f - colorStep;
	}
}

// Loads texture for the text from .apk
void WinnerText::loadTexture()
{
	// Don't load again if already loaded
	if (texture)
		return;

	// Load texture from file
	int width, height;
	texture0 = loadTextureFromPNG("assets/blue_wins.png", width, height);
	texture1 = loadTextureFromPNG("assets/pink_wins.png", width, height);

	// Set up texture coords
	texCoords[0] = 1.0f;	texCoords[1] = 0.0f;
	texCoords[2] = 1.0f;	texCoords[3] = 1.0f;
	texCoords[4] = 0.0f;	texCoords[5] = 1.0f;
	texCoords[6] = 0.0f;	texCoords[7] = 1.0f;
	texCoords[8] = 0.0f;	texCoords[9] = 0.0f;
	texCoords[10] = 1.0f;	texCoords[11] = 0.0f;

	// Set up vertex colors
	for (int i = 0; i < vertCount; ++i)
	{
		colors[(i*4)+0] = 1.0f;
		colors[(i*4)+1] = 1.0f;
		colors[(i*4)+2] = 1.0f;
		colors[(i*4)+3] = 1.0f;
	}
}

// Resets text position and destination
void WinnerText::reset()
{
	if (playerId == 1)
	{
		pos.x = 3.0f;
		dest.x = -2.6f;
	}
	else
	{
		pos.x = -3.0f;
		dest.x = 2.6f;
	}
}
