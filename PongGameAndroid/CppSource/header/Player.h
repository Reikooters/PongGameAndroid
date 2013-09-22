#pragma once

#include "Vector2.h"

class Player
{
	// Height and width of the paddle.
	const float height, width;

	// Current and destination position of the paddle
	Vector2 pos, dest;

	// Vertices that make up triangles to create the paddle
	float* verts;

	// Recalculates vertices that make up triangles to create the paddle
	void recalcVerts();

	// Whether or not vertices need to be recalculated.
	bool dirty;

	// Moves player toward destination position
	void updatePos();

public:
	// Constructor. Iniitialises variables.
	Player();

	// Draws the player
	void draw();

	// Sets the position of the player. Sets dirty if new position is not the current one.
	void setPos(const float x, const float y);

	// Returns the current position of the player.
	Vector2 getPos();

	// Sets destination position of the paddle
	void moveTo(const float y);

	// Updates Player status (such as position)
	void update();
};
