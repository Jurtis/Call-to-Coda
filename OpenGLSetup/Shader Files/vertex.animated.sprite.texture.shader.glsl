#version 330 core
// layout (location = 0) in vec3 vertexPosition;
// layout (location = 1) in vec2 inputTexCoords;
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform int animationIndex;
uniform float frameSize; // Size of each frame as a fraction of the texture size

void main()
{
	gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);

	TexCoords = vertex.zw * vec2(frameSize, 1.0) + vec2(animationIndex * frameSize, 0.0);
	//TexCoords = vertex.zw + vec2(animationIndex * frameSize, 0.0);
}