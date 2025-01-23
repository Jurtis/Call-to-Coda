#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture2D
{
public:
	// holds the ID of the texture object, used for all texture operations to reference to this texture
	unsigned int ID;
	// texture image dimensions
	unsigned int Width, Height;
	// texture format
	unsigned int internalFormat; // format of texture object
	unsigned int imageFormat; // format of loaded image
	// texture configuration
	unsigned int wrapS; // wrapping mode on S axis
	unsigned int wrapT; // wrapping mode on T axis
	unsigned int filterMin; // filtering mode if texture pixel < screen pixels
	unsigned int filterMax; // filtering mode if texture pixel > screen pixels
	// constructor (sets default texture modes)
	Texture2D();
	/// generates texture from image data
	void Generate(unsigned int width, unsigned int height, unsigned char* data);
	// binds the texture as the current active GL_TEXTURE_2D texture object
	void Bind() const;
};

#endif
