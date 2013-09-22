#include "Vector2.h"

class InputManager
{
	struct Pointer
	{
		bool active;
		int pointerId;
		Vector2 pos;
	};

	Pointer pointer[4];

public:
	InputManager();

	void addPointer(const int pointerId, const float x, const float y);
	void movePointer(const int pointerId, const float x, const float y);
	void removePointer(const int pointerId);
};
