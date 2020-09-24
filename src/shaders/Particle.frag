#version 330 core

// FROM OPEN GL TUTORIALS
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// Interpolated values from the vertex shaders
in vec3 particle_color;

// Ouput data
out vec3 color;

void main() {
  // Output color = color of the texture at the specified UV
  color = particle_color;
}