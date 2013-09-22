#include "Player.h"

#include "Application.h"

extern Application* app;

// Constructor
Player::Player()
{

}

// Draws the player on the screen.
void Player::draw()
{
	/*
	glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    glEnableVertexAttribArray(gvPositionHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
	*/

	const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
        0.5f, -0.5f };

	glUseProgram(app->gProgram);
	glVertexAttribPointer(app->gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    glEnableVertexAttribArray(app->gvPositionHandle);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
