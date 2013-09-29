#pragma once

#include "GameObject.h"

class ScoreToken : public GameObject
{
	// Recalculates vertices that make up triangles to create the score token
	void recalcVerts();

	// Moves the score token toward destination position
	void updatePos();

public:
	// Player Id for this score token
	int playerId;

	// Constructor. Iniitialises variables.
	ScoreToken();

	// Destructor. Frees memory.
	~ScoreToken();

	// Loads texture for the score token from .apk
	void loadTexture();

	// Draws the score token
	void draw();

	// Sets the position of the score token. Sets dirty if new position is not the current one.
	void setPos(const float x, const float y);

	// Updates Score Token status (such as position)
	void update();
};
