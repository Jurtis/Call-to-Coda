#include "game_object.h"

#include <iostream>

GameObject::GameObject() : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), HasHitbox(false), Destroyed(false), AnimationIndex(0), FrameCount(1) { }

GameObject::GameObject(glm::vec2 position, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity, int animationIndex, int frameCount) : Position(position), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), HasHitbox(false), Destroyed(false), AnimationIndex(animationIndex), FrameCount(frameCount) { }

void GameObject::Draw(SpriteRenderer& renderer)
{
	if (!this->Destroyed)
	{
		renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
	}
};
/*
void GameObject::DrawAnimated(SpriteRenderer& renderer, int animationIndex, int frameCount)
{
	if (!this->Destroyed)
	{
		renderer.DrawAnimatedSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color, animationIndex, frameCount);
	}
};
*/

void GameObject::DrawAnimated(SpriteRenderer& renderer, int animationIndex, int frameCount)
{
	if (!this->Destroyed)
	{
		renderer.DrawAnimatedSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color, this->AnimationIndex, this->FrameCount);
	}
};

void GameObject::Animate(float deltaTime, int frameCount, float duration)
{
	while (elapsedTime > duration)
		elapsedTime -= duration;

	//std::cout << "bruh" << std::endl;

	AnimationIndex = (int)((elapsedTime / duration) * FrameCount);
	/*
	if (AnimationIndex >= FrameCount)
	{
		//AnimationIndex = FrameCount - 1;
		AnimationIndex = ;
		//return frameCount;
	}
	*/
};

/*
void GameObject::Animate(float deltaTime, int frameCount, float duration)
{
	while (this->elapsedTime > duration)
		this->elapsedTime -= duration;

	//int animationIndex = (int)((*time / duration) * frameCount);
	//this->AnimationIndex = (int)((*deltaTime / duration) * frameCount);
	this->AnimationIndex = (int)((this->elapsedTime / duration) * this->FrameCount);

	if (this->AnimationIndex >= this->FrameCount)
	{
		this->AnimationIndex = this->FrameCount - 1;
		//return frameCount;
	}
};
*/

/*
int GameObject::Animate(float* deltaTime, int frameCount, float duration)
{
	while (*deltaTime > duration)
		*deltaTime -= duration;

	//int animationIndex = (int)((*time / duration) * frameCount);
	//this->AnimationIndex = (int)((*deltaTime / duration) * frameCount);
	this->AnimationIndex = (int)((*deltaTime / duration) * this->FrameCount);

	if (this->AnimationIndex >= this->FrameCount)
	{
		this->AnimationIndex = this->FrameCount - 1;
		//return frameCount;
	}

	return this->AnimationIndex;
};
*/

void GameObject::AddTime(float deltaTime)
{
	this->elapsedTime += deltaTime;
}

void GameObject::SetTime(float timeInput)
{
	this->elapsedTime = timeInput;
}