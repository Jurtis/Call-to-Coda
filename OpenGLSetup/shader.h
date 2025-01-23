#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>


// General purpose shader object.
// Compiles from files, generates compile/link-time error
// messages and hosts several utility functions for easy management.
class Shader
{
public:
	// the program ID [state]
	unsigned int ID;
	// constructor
	Shader() {}
	// use/activate shader
	Shader &Use();
	// compiles the shader from given source code
	void	Compile(const char* vertexSource, const char* fragmentSource);
	// utility uniform functions
	void	setInt		(const char* name, int value, bool useShader = false);
	void	setFloat	(const char* name, float value, bool useShader = false);
	void	SetVector2f	(const char* name, float x, float y, bool useShader = false);
	void	SetVector2f	(const char* name, const glm::vec2 &value, bool useShader = false);
	void	SetVector3f	(const char* name, float x, float y, float z, bool useShader = false);
	void	SetVector3f	(const char* name, const glm::vec3 &value, bool useShader = false);
	void	SetVector4f	(const char* name, float x, float y, float z, float w, bool useShader = false);
	void	SetVector4f	(const char* name, const glm::vec4 &value, bool useShader = false);
	void	SetMatrix4	(const char* name, const glm::mat4 &matrix, bool useShader = false);
};

#endif