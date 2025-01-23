#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

class PlayerObject : public GameObject
{
public:
	glm::vec2 Acceleration;

	PlayerObject();

	PlayerObject(glm::vec2 position, glm::vec2 size, Texture2D sprite, glm::vec2 velocity = glm::vec2(0.0f), glm::vec2 acceleration = glm::vec2(0.0f));

	glm::vec2 Move(float deltaTime, unsigned int window_width);

	//void Reset(glm::vec2 position);

	void SetRightDodgeVars();

	void SetLeftDodgeVars();
};

#endif