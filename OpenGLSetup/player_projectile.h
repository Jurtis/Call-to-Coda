#ifndef PLAYER_PROJECTILE_H
#define PLAYER_PROJECTILE_H

#include "game_object.h"

class PlayerProjectileObject : public GameObject
{
public:
	PlayerProjectileObject();

	PlayerProjectileObject(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 Move(float deltaTime, unsigned int window_width);
	//void Reset(glm::vec2 position, glm::vec2 velocity);
	void Reset(glm::vec2 position);
};



#endif