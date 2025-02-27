#include "text_renderer.h"
#include "resource_manager.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>>
#include <ft2build.h>
#include FT_FREETYPE_H



// Constructor
TextRenderer::TextRenderer(unsigned int width, unsigned int height)
{
	// load and configure shader
	this->TextShader = ResourceManager::LoadShader("Shader Files/vertex.text.shader.glsl", "Shader Files/fragment.text.shader.glsl", "text");
	//this->TextShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f), true);
	this->TextShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height)), true);
	this->TextShader.setInt("text", 0);
	// Configure VAO/VBO for texture quads
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

/*
// Destructor
TextRenderer::~TextRenderer()
{
	//glDeleteVertexArrays(1, &this->quadVAO);
	for (auto& pair : this->Characters)
		glDeleteTextures(1, &pair.second.TextureID);
	glDeleteVertexArrays(1, &this->TextVAO);
	glDeleteBuffers(1, &this->TextVBO);
}
*/

void TextRenderer::Load(std::string font, unsigned int fontSize)
{
	// first clear the previous loaded characters
	this->Characters.clear();

	// FreeType Initialization
	FT_Library ft;

	// Error checking
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library";
	}

	FT_Face face;
	if (FT_New_Face(ft, font.c_str(), 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}
	else
	{
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, fontSize);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// load first 128 characters of ASCII set
		for (GLubyte c = 0; c < 128; c++)
		{
			// Load character glyph
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			// now store character for later use
			Character character = { texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), static_cast<unsigned int>(face->glyph->advance.x) };
			this->Characters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// destroy FreeType after process is complete
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}


void TextRenderer::DrawText(std::string text, float x, float y, float scale, glm::vec3 color)
{
	// activate corresponding render state
	this->TextShader.Use();
	//glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
	this->TextShader.SetVector3f("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->VAO);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = this->Characters[*c];

		float xPosition = x + ch.Bearing.x * scale;
		float yPosition = y - (ch.Size.y - ch.Bearing.y) * scale;

		float width = ch.Size.x * scale;
		float height = ch.Size.y * scale;

		// update VBO for each character
		float vertices[6][4] = {
			{ xPosition, yPosition + height, 0.0f, 0.0f },
			{ xPosition, yPosition, 0.0f, 1.0f },
			{ xPosition + width, yPosition, 1.0f, 1.0f },

			{ xPosition, yPosition + height, 0.0f, 0.0f },
			{ xPosition + width, yPosition, 1.0f, 1.0f },
			{ xPosition + width, yPosition + height, 1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels_
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}