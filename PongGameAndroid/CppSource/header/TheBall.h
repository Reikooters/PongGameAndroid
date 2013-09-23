#pragma once

#include "GameObject.h"

class TheBall : public GameObject
{
	// Current step in animating the ball's color
	float colorStep;

	// Recalculates vertices that make up triangles to create the ball
	void recalcVerts();

	// Moves the ball toward destination position
	void updatePos();

	// Animates the ball's color
	void updateColor();

	// Ball travel direction
	Vector2 direction;

public:
	// Constructor. Iniitialises variables.
	TheBall();

	// Destructor. Frees memory.
	~TheBall();

	// Draws the ball
	void draw();

	// Sets the position of the ball. Sets dirty if new position is not the current one.
	void setPos(const float x, const float y);

	// Updates Ball status (such as position)
	void update();

	// Reset ball back to starting position. Called after a player scores.
	void reset();
};
