#include "TapToPlayText.h"

#include "Application.h"
#include "Renderer.h"
#include "Timer.h"
#include "Vector2.h"

// Contains loadTextureFromPNG()
#include "utils.h"

extern Application* app;

// Constructor. Iniitialises variables.
TapToPlayText::TapToPlayText()
	//: GameObject(0.9f, 0.047f * (1080.0f / 1920.0f), // height and width - viewing phone horizontally
	: GameObject(0.3f, 1.25f, // height and width - viewing phone horizontally
	0.0f, // speed
	Vector2()), // position
	vertCount(6),
	colorDir(true)
{
	verts = new GLfloat[vertCount * 2]; // 2 dimensional coords
	colors = new GLfloat[vertCount * 4]; // 4 floats make up each color
	texCoords = new GLfloat[vertCount * 2]; // 2 dimensional coords

	pos.y = -0.75f;
}

TapToPlayText::~TapToPlayText()
{
	delete[] verts;
	delete[] colors;
	delete[] texCoords;
}

// Draws the text on the screen.
void TapToPlayText::draw()
{
	// Draw only if object is visible
	if (!visible) return;

	app->getRenderer()->drawArray(verts, vertCount, colors, texCoords, texture);
}

// Sets the position of the text. Sets dirty if new position is not the current one.
void TapToPlayText::setPos(const float x, const float y)
{
	GameObject::setPos(x, y);
}

// Recalculates vertices that make up triangles to create the text
void TapToPlayText::recalcVerts()
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
void TapToPlayText::update()
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
void TapToPlayText::updatePos()
{
	
}

// Animates the text's color
void TapToPlayText::updateColor()
{
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
void TapToPlayText::loadTexture()
{
	// Don't load again if already loaded
	if (texture)
		return;

	// Load texture from file
	int width, height;
	texture = loadTextureFromPNG("assets/tap_screen_to_play.png", width, height);

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
