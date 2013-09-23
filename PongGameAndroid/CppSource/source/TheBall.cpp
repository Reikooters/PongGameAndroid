#include "TheBall.h"

#include "Application.h"
#include "Renderer.h"
#include "Timer.h"
#include "Player.h"
#include "Vector2.h"

extern Application* app;

// Constructor. Iniitialises variables.
TheBall::TheBall()
	: GameObject(0.077f, 0.077f * (1080.0f / 1920.0f), // height and width of ball - viewing phone horizontally
	0.000011f, // speed
	Vector2()), // position
	colorStep(0.8f) // color
{
	verts = new GLfloat[12]; // 6 points, 2 dimensional coords
	colors = new GLfloat[24]; // 6 points, 4 floats make up each color

	direction.x = 0.07f * (1080.0f / 1920.0f);
	direction.y = 0.07f;
}

TheBall::~TheBall()
{
	delete[] verts;
	delete[] colors;
}

// Draws the player on the screen.
void TheBall::draw()
{
	app->getRenderer()->drawArray(verts, 6, colors);
}

// Sets the position of the player. Sets dirty if new position is not the current one.
void TheBall::setPos(const float x, const float y)
{
	GameObject::setPos(x, y);

	const float wall = 0.95f;
	const float goal = 1.4f;

	/* Assumes both paddles are the same distance away from the center and are the
	 * same width. */
	const float paddle = app->getPlayer(0)->getPos().x // paddle position
						 - (app->getPlayer(0)->getWidth() / 2.0f) // paddle width
						 - (width / 2.0f); // ball width

	// Clamp ball position and bounce off walls
	if ((pos.y < -wall && direction.y < 0.0f) || (pos.y > wall && direction.y > 0.0f))
		direction.y = -direction.y;

	// Scored a goal
	if ((pos.x < -goal && direction.x < 0.0f) || (pos.x > goal && direction.x > 0.0f))
	{
		if (direction.x < 0.0f) app->score(1); // blue scored
		else app->score(0); // pink scored
	}

	// Bounce off paddles
	// Check if aligned with a paddle
	if (((pos.x < -paddle && pos.x > -paddle - app->getPlayer(0)->getWidth()) && direction.x < 0.0f)
		|| ((pos.x > paddle && pos.x < paddle + app->getPlayer(0)->getWidth()) && direction.x > 0.0f))
	{
		// Check if paddle hit the ball
		Player* nearPlayer;
		float nearPlayerPos;
		float nearPlayerHeight;

		// Ball is near blue player
		if (pos.x < 0.0f) nearPlayer = app->getPlayer(1);
		// Ball is near pink player
		else if (pos.x > 0.0f) nearPlayer = app->getPlayer(0);

		nearPlayerPos = nearPlayer->getPos().y;
		nearPlayerHeight = nearPlayer->getHeight();

		// Top and bottom of paddle
		float pMin, pMax;
		pMin = (nearPlayerPos - (nearPlayerHeight / 2.0f)) + 1.0f; // +1.0f to make all values positive
		pMax = (nearPlayerPos + (nearPlayerHeight / 2.0f)) + 1.0f;

		// Top and bottom of ball
		float bMin, bMax;
		bMin = (pos.y - (height / 2.0f)) + 1.0f;
		bMax = (pos.y + (height / 2.0f)) + 1.0f;

		// The ball hit
		if (bMax > pMin && bMin < pMax)
			direction.x = -direction.x;
	}
}

// Recalculates vertices that make up triangles to create the paddle
void TheBall::recalcVerts()
{
	// Recalc only if dirty
	if (!dirty)
		return;

	// Calculate paddle corner coordinates
	float x1 = pos.x - (width / 2);
	float x2 = pos.x + (width / 2);
	float y1 = pos.y - (height / 2);
	float y2 = pos.y + (height / 2);

	// Lower right triangle
	verts[0] = y1;
	verts[1] = x1;

	verts[2] = y2;
	verts[3] = x1;

	verts[4] = y2;
	verts[5] = x2;

	// Upper left triangle
	verts[6] = y2;
	verts[7] = x2;

	verts[8] = y1;
	verts[9] = x2;

	verts[10] = y1;
	verts[11] = x1;

	// Remove dirty flag
	dirty = false;
}

// Updates Player status (such as position)
void TheBall::update()
{
	// Update ball position
	updatePos();

	// Update ball color
	updateColor();

	// Recalculate verts if needed
	if (dirty)
		recalcVerts();
}

// Moves player toward destination position
void TheBall::updatePos()
{
	setPos(pos.x + (direction.x * speed * app->dt),
		   pos.y + (direction.y * speed * app->dt));
}

// Animates the player's color
void TheBall::updateColor()
{
	// Make player color blink
    colorStep += 0.003f;
    if (colorStep > 1.0f) colorStep = 0.8f;
	else if (colorStep < 0.8f) colorStep = 0.8f;

	for (int i = 0; i < 6; ++i)
	{
		colors[(i*4)+0] = colorStep;
		colors[(i*4)+1] = colorStep * 0.8f;
		colors[(i*4)+2] = 0.2f;
		colors[(i*4)+3] = 1.0f;
	}
}

void TheBall::reset()
{
	pos.x = 0.0f;
	pos.y = 0.0f;
	direction.x = -direction.x;
	dirty = true;
}