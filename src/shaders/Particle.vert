#version 440 core

// Input vertex data. Only position and color for now.
layout(location = 0) in vec3 vpos;
layout(location = 1) in vec3 vcolor;

// Output data. Only color for now. We'll change position by setting
// gl_position.
out vec3 particle_color;

// Constants. ModelViewProjection Matrix
uniform mat4 MVP;

void main() {
  // Output position of the vertex, in clip space : MVP * position
  gl_Position = MVP * vec4(vpos, 1);

  // UV of the vertex. No special space for this one.
  // particle_color = vcolor;
  particle_color = vcolor;
}