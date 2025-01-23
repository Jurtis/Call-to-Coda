#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "shader.h"
//#include "text_character.h"
#include "texture.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <iostream>
#include <map>

//#include <ft2build.h>
//#include FT_FREETYPE_H

// Data relevant to each character loaded using FreeType
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2 Size; // Size of glyph
	glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
	unsigned int Advance; // Horizontal offset to advance to next glyph
};


class TextRenderer
{
public:
	// Constructor
	//TextRenderer(Shader& shader);
	TextRenderer(unsigned int width, unsigned int height);

	// Destructor
	//~TextRenderer();

	// Renders a string of text using the precompiled list of characters
	void DrawText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));

	// Pre-compiles a list of characters from the given font
	void Load(std::string font, unsigned int fontSize);

	// Holds a list of pre-compiled characters
	std::map<char, Character> Characters;

	// Shader used for text rendering
	Shader TextShader;

	//void DrawText(Shader& shader, std::string text, float x, float y, float scale, glm::vec3 color);
	//void DrawText(std::string text, float x, float y, float scale, glm::vec3 color);
private:
	// Render state
	//Shader			shader;
	unsigned int	VAO;
	unsigned int	VBO;
	//unsigned int	quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	//void initRenderData();

	//int initFreeTypeData();

	//std::map<GLchar, Character> Characters;


};

#endif