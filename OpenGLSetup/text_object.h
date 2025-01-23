#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

//#include "texture.h"
#include "text_renderer.h"

class TextObject
{
public:
	// object state			std::string text, float x, float y, float scale, glm::vec3 color
	std::string Text;
	float X, Y, Scale;
	glm::vec3 Color;
	//glm::vec2 Position, Size, Velocity;
	//glm::vec3 Color;
	//float Rotation;
	//bool HasHitbox;
	//bool Destroyed;
	// render state
	//Texture2D Sprite;
	// constuctor(s)
	TextObject();
	//TextObject(glm::vec2 position, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
	TextObject(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));
	// draw
	void Draw(TextRenderer& renderer);
};

#endif