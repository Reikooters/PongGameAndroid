#pragma once

#include "GameObject.h"

class TitleText : public GameObject
{
	// Current step in animating the title text's color
	float colorStep;
	bool colorDir;

	// Recalculates vertices that make up triangles to create the title text
	void recalcVerts();

	// Moves the title text toward destination position
	void updatePos();

	// Animates the title text's color
	void updateColor();

	// Number of vertices in the object
	int vertCount;

public:
	// Constructor. Iniitialises variables.
	TitleText();

	// Destructor. Frees memory.
	~TitleText();

	// Loads texture for the title text from .apk
	void loadTexture();

	// Draws the title text
	void draw();

	// Sets the position of the title text. Sets dirty if new position is not the current one.
	void setPos(const float x, const float y);

	// Updates Title Text status (such as position)
	void update();
};
