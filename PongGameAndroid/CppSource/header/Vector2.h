#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2(const float x, const float y)
		: x(x), y(y)
	{
	}
};
