#include "TitleText.h"

#include "Application.h"
#include "Renderer.h"
#include "Timer.h"
#include "Vector2.h"

extern Application* app;

// Constructor. Iniitialises variables.
TitleText::TitleText()
	: GameObject(0.9f, 0.047f * (1080.0f / 1920.0f), // height and width - viewing phone horizontally
	0.0f, // speed
	Vector2()), // position
	vertCount(25),
	colorDir(true)
{
	verts = new GLfloat[vertCount * 2]; // 2 dimensional coords
	colors = new GLfloat[vertCount * 4]; // 4 floats make up each color

	for (int i = 0; i < vertCount; ++i)
	{
		colors[(i*4)+0] = 1.0f;
		colors[(i*4)+1] = 1.0f;
		colors[(i*4)+2] = 1.0f;
		colors[(i*4)+3] = 0.3f;
	}
}

TitleText::~TitleText()
{
	delete[] verts;
	delete[] colors;
}

// Draws the title text on the screen.
void TitleText::draw()
{
	return; // disabled for now

	// Draw only if object is visible
	if (!visible) return;

	app->getRenderer()->drawArray(verts, vertCount, colors);
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

	// Calculate paddle corner coordinates
	/*
	//float x1 = pos.x - (width / 2);
	//float x2 = pos.x + (width / 2);
	//float y1 = pos.y - (height / 2);
	//float y2 = pos.y + (height / 2);
	float x1 = -1.0f;
	float x2 = 1.0f;
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
	*/

	// P
	/*
	verts[0] = -0.6f;	verts[1] = -0.3f;
	verts[2] = -0.5f;	verts[3] = 0.3f;
	verts[4] = -0.4f;	verts[5] = 0.1f;
	verts[6] = -0.4f;	verts[7] = 0.1f;
	verts[8] = -0.2f;	verts[9] = 0.2f;
	verts[10] = -0.5f;	verts[11] = 0.3f;
	*/

	// P
	verts[0]  = -0.6f;	verts[1]  = 0.6f;
	verts[2]  = 0.5f;	verts[3]  = 0.5f;
	verts[4]  = 0.0f;	verts[5]  = 0.45f;
	verts[6]  = 0.0f;	verts[7]  = 0.45f;
	verts[8]  = 0.35f;	verts[9]  = 0.2f;
	verts[10] = 0.5f;	verts[11] = 0.5f;

	// O
	verts[12] = -0.45f;	verts[13] = 0.25f;
	verts[14] = -0.175f;	verts[15] = 0.4f;
	verts[16] = -0.175f;	verts[17] = 0.1f;
	verts[18] = 0.1f;	verts[19] = 0.25f;
	verts[20] = -0.175f;	verts[21] = 0.4f;
	verts[22] = -0.175f;	verts[23] = 0.1f;

	// N
	// left
	verts[24] = -0.5f;	verts[25] = 0.0f;
	verts[26] = -0.5f;	verts[27] = 0.07f;
	verts[28] = 0.1;	verts[29] = 0.0f;
	// right
	verts[30] = -0.5f;	verts[31] = -0.1f;
	verts[32] = -0.5f;	verts[33] = -0.17f;
	verts[34] = -0.1f;	verts[35] = -0.1f;
	// middle top
	verts[36] = -0.2f;	verts[37] = 0.0f;
	verts[38] = -0.3f;	verts[39] = 0.0f;
	verts[40] = -0.1f;	verts[41] = -0.1f;
	// middle bottom
	verts[42] = -0.2f;	verts[43] = 0.0f;
	verts[44] = -0.2f;	verts[45] = -0.1f;
	verts[46] = -0.1f;	verts[47] = -0.1f;

	// G

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
