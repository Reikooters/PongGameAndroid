#pragma once

#include "Vector2.h"

class GameObject
{
protected:
	// Height and width of the object.
	const float height, width;

	// Object's movement speed.
	float speed;

	// Current and destination position of the object
	Vector2 pos, dest;

	// Vertices that make up triangles to create the object
	float* verts;

	// Vertex color buffer for the object
	float* colors;

	// Recalculates vertices that make up triangles to create the object
	virtual void recalcVerts() = 0;

	// Whether or not vertices need to be recalculated.
	bool dirty;

	// Moves object toward destination position
	virtual void updatePos();

public:
	GameObject();
	GameObject(float height, float width, float speed, Vector2 pos);
	virtual ~GameObject();

	// Draws the object
	virtual void draw() = 0;

	// Sets the position of the object. Sets dirty if new position is not the current one.
	virtual void setPos(const float x, const float y);

	// Returns the current position of the player.
	virtual Vector2 getPos() const;

	// Sets destination position of the object.
	virtual void moveTo(const float y);

	// Updates Player status (such as position)
	virtual void update() = 0;

	// Returns the height of the object
	virtual float getHeight() const;

	// Returns the width of the object
	virtual float getWidth() const;
};
