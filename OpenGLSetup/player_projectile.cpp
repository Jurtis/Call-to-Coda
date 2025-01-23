#include "player_projectile.h"

PlayerProjectileObject::PlayerProjectileObject() : GameObject() { }

PlayerProjectileObject::PlayerProjectileObject(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, Texture2D sprite) : GameObject(position, size, sprite, glm::vec3(1.0f), velocity) { }

glm::vec2 PlayerProjectileObject::Move(float deltaTime, unsigned int window_width)
{
	this->Position += this->Velocity * deltaTime;
	return this->Position;
}

void PlayerProjectileObject::Reset(glm::vec2 position)
{
	this->Position = position;
}