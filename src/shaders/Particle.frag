#version 330 core

// FROM OPEN GL TUTORIALS http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 particlecolor;

// Ouput data
out vec4 color;

uniform sampler2D myTextureSampler;

void main(){
	// Output color = color of the texture at the specified UV
	color = texture( myTextureSampler, UV ) * particlecolor;

}