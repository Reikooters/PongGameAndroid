#pragma once

#include "Vector2.h"

class Player
{
	const float height;
	const float width;
	Vector2 pos;
	float* verts;

	void recalcVerts();

public:
	Player();
	void draw();
	void setPos(const float x, const float y);
};
