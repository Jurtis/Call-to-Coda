#include "player.h"
#include <cmath>

PlayerObject::PlayerObject() : GameObject(), Acceleration(0.0f, 0.0f) { }

PlayerObject::PlayerObject(glm::vec2 position, glm::vec2 size, Texture2D sprite, glm::vec2 velocity, glm::vec2 acceleration) : GameObject(position, size, sprite, glm::vec3(1.0f), velocity), Acceleration(acceleration) { }


//PlayerObject::PlayerObject(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, Texture2D sprite, glm::vec2 acceleration) : GameObject(position, size, sprite, glm::vec3(1.0f), velocity) { }

glm::vec2 PlayerObject::Move(float deltaTime, unsigned int window_width)
{
	//if (this->Position.x != (window_width / 2.0f - this->Size.x / 2.0f))
	//if ((this->Position.x - (window_width / 2.0f - this->Size.x / 2.0f)) > 0.001f)
	/*
	if (pow((this->Position.x - (window_width / 2.0f - this->Size.x / 2.0f)), 2) > 0.1f)
	{
		this->Position += this->Velocity * deltaTime;
		this->Velocity -= this->Acceleration * deltaTime;
	}
	*/
	//if (std::abs(this->Position.x - (window_width / 2.0f - this->Size.x / 2.0f)) > 0.1f)
	if (std::abs(this->Position.x - 350.0f) > 1.1f)
	{
		this->Position += this->Velocity * deltaTime;
		this->Velocity -= this->Acceleration * deltaTime;
	}
	else
	{
		this->Position.x = 350.0f;
		this->Velocity.x = 0.0f;
	}
	//this->Position += this->Velocity * deltaTime;
	//this->Velocity -= this->Acceleration * deltaTime;
	return this->Position;
}

void PlayerObject::SetRightDodgeVars()
{
	this->Velocity = { -3000.0f, 0.0f };
	this->Acceleration = { -22000.0f, 0.0f };
	//this->Velocity = { -750.0f, 0.0f };
	//this->Acceleration = { -5500.0f, 0.0f };
	
}

void PlayerObject::SetLeftDodgeVars()
{
	//this->Velocity = { 750.0f, 0.0f };
	//this->Acceleration = { 5500.0f, 0.0f };
	//this->Velocity = { 1500.0f, 0.0f };
	//this->Acceleration = { 11000.0f, 0.0f };
	this->Velocity = { 3000.0f, 0.0f };
	this->Acceleration = { 22000.0f, 0.0f };
}

/*
class PlayerObject : public GameObject
{
	glm::vec2 acceleration;

	PlayerObject();

	PlayerObject(glm::vec2 position, glm::vec2 size, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 Move(float deltaTime);

	void Reset(glm::vec2 position);

	void SetRightDodgeVars();

	void SetLeftDodgeCars();
};
*/