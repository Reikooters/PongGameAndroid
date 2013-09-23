#pragma once

#include "Vector2.h"
#include "GameObject.h"

class Player : public GameObject
{
	// Color of the paddle. 0 = Orange, 1 = Red.
	int color;

	// Recalculates vertices that make up triangles to create the paddle
	void recalcVerts();

	// Moves player toward destination position
	void updatePos();

public:
	// Constructor. Iniitialises variables.
	Player();

	// Destructor. Frees memory.
	~Player();

	// Draws the player
	void draw();

	// Sets the position of the player. Sets dirty if new position is not the current one.
	void setPos(const float x, const float y);

	// Updates Player status (such as position)
	void update();

	// Sets the paddle color. 0 = Orange, 1 = Red.
	void setColor(int color);
};
