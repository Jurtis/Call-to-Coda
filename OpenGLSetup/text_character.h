#ifndef TEXT_CHARACTER_H
#define TEXT_CHARACTER_H

//#include <glad/glad.h>
#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>

// Data relevant to each character loaded using FreeType
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2 Size; // Size of glyph
	glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
	unsigned int Advance; // Horizontal offset to advance to next glyph
};

#endif