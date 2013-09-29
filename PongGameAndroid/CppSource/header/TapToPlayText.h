#pragma once

#include "GameObject.h"

class TapToPlayText : public GameObject
{
	// Current step in animating the text's color
	float colorStep;
	bool colorDir;

	// Recalculates vertices that make up triangles to create the text
	void recalcVerts();

	// Moves the text toward destination position
	void updatePos();

	// Animates the text's color
	void updateColor();

	// Number of vertices in the object
	int vertCount;

public:
	// Constructor. Iniitialises variables.
	TapToPlayText();

	// Destructor. Frees memory.
	~TapToPlayText();

	// Loads texture for the text from .apk
	void loadTexture();

	// Draws the text
	void draw();

	// Sets the position of the text. Sets dirty if new position is not the current one.
	void setPos(const float x, const float y);

	// Updates Text status (such as position)
	void update();
};
