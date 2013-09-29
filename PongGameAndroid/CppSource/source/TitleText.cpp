#include "TitleText.h"

#include "Application.h"
#include "Renderer.h"
#include "Timer.h"
#include "Vector2.h"

// Contains loadTextureFromPNG()
#include "utils.h"

extern Application* app;

// Constructor. Iniitialises variables.
TitleText::TitleText()
	//: GameObject(0.9f, 0.047f * (1080.0f / 1920.0f), // height and width - viewing phone horizontally
	: GameObject(1.0f, 1.0f, // height and width - viewing phone horizontally
	0.0f, // speed
	Vector2()), // position
	vertCount(6),
	colorDir(true)
{
	verts = new GLfloat[vertCount * 2]; // 2 dimensional coords
	colors = new GLfloat[vertCount * 4]; // 4 floats make up each color
	texCoords = new GLfloat[vertCount * 2]; // 2 dimensional coords
}

TitleText::~TitleText()
{
	delete[] verts;
	delete[] colors;
	delete[] texCoords;
}

// Draws the title text on the screen.
void TitleText::draw()
{
	// Draw only if object is visible
	if (!visible) return;

	app->getRenderer()->drawArray(verts, vertCount, colors, texCoords, texture);
}

// Sets the position of the title text. Sets dirty if new position is not the current one.
void TitleText::setPos(const float x, const float y)
{
	GameObject::setPos(x, y);
}

// Recalculates vertices that make up triangles to create the title text
void TitleText::recalcVerts()
{
	// Recalc only if dirty
	if (!dirty)
		return;

	float x1 = -1.0f;
	float x2 = 1.0f;
	float y1 = -1.0f;
	float y2 = 1.0f;

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

// Updates Title Text status (such as position)
void TitleText::update()
{
	// Update title text position
	updatePos();

	// Update title text color
	updateColor();

	// Recalculate verts if needed
	if (dirty)
		recalcVerts();
}

// Moves title text toward destination position
void TitleText::updatePos()
{
	
}

// Animates the title text's color
void TitleText::updateColor()
{
	return; // disabled for now

	if (colorDir)
		colorStep += 0.048f;
	else
		colorStep -= 0.048f;

	if (colorStep > 0.4f) { colorStep = 0.4f; colorDir = !colorDir; }
	else if (colorStep < 0.0f) { colorStep = 0.0f; colorDir = !colorDir; }

	for (int i = 0; i < vertCount; ++i)
	{
		colors[(i*4)+0] = 1.0f - colorStep * (0.66f + ((i / (float)vertCount) / 3.0f));
		colors[(i*4)+1] = 0.4f - colorStep;
		colors[(i*4)+2] = 1.0f - colorStep * (0.66f + ((i / (float)vertCount) / 3.0f));
		colors[(i*4)+3] = 1.0f;
	}
}

// Loads texture for the title text from .apk
void TitleText::loadTexture()
{
	// Don't load again if already loaded
	if (texture)
		return;

	// Load texture from file
	int width, height;
	texture = loadTextureFromPNG("assets/title.png", width, height);

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
