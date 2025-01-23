#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"

class GameObject
{
public:
	// object state
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	float Rotation;
	bool HasHitbox;
	bool Destroyed;
	int AnimationIndex;
	int FrameCount;
	// render state
	Texture2D Sprite;
	// constuctor(s)
	GameObject();
	GameObject(glm::vec2 position, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f), int animationIndex = 0, int frameCount = 1);
	// draw
	virtual void Draw(SpriteRenderer& renderer);
	virtual void DrawAnimated(SpriteRenderer& renderer, int animationIndex, int frameCount);
	//virtual int Animate(float* time, int frameCount, float duration = 1.0f);
	virtual void Animate(float time, int frameCount, float duration = 1.0f);
	virtual void AddTime(float deltaTime);
	void SetTime(float timeInput);

private:
	float elapsedTime = 0.0f;    // Time accumulator
};

#endif