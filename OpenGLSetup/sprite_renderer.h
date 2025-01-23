#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "shader.h"
#include "texture.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class SpriteRenderer
{
public:
	// Constructor
	SpriteRenderer(Shader& shader);
	// Destructor
	~SpriteRenderer();
	// Renders a defined quad textured with given sprite [A 4 Sided 2D Vector with a Texture]
	void DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

	void DrawAnimatedSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f), int animationIndex = 0, int frameCount = 1);
private:
	// Render state
	Shader			shader;
	unsigned int	quadVAO;
	unsigned int	SpriteVBO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif