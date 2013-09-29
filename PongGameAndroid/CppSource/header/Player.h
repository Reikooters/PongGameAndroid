#pragma once

#include "GameObject.h"

class Player : public GameObject
{
	// Color of the paddle. 0 = Pink, 1 = Blue.
	int color;
	float colorStep;

	// Recalculates vertices that make up triangles to create the paddle
	void recalcVerts();

	// Moves player toward destination position
	void updatePos();

	// Animates the player's color
	void updateColor();

public:
	// Player Id for this player
	int playerId;

	// Constructor. Iniitialises variables.
	Player();

	// Destructor. Frees memory.
	~Player();

	// Loads texture for the player from .apk
	void loadTexture();

	// Draws the player
	void draw();

	// Sets the position of the player. Sets dirty if new position is not the current one.
	void setPos(const float x, const float y);

	// Updates Player status (such as position)
	void update();

	// Sets the paddle color. 0 = Pink, 1 = Blue.
	void setColor(const int color);
};
