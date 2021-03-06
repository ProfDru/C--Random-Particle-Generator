#version 440 core

// Input vertex data. Only position and color for now.
layout(location = 0) in vec3 vpos;
layout(location = 1) in vec3 vcolor;

// Output data. Only color for now. We'll change position by setting
// gl_position.
out vec3 particle_color;

// Constants. ModelViewProjection Matrix
uniform mat4 MVP;
uniform vec2 g_Resolution;

const float point_size = 10.0;

void main() {
  // Output position of the vertex, in clip space : MVP * position
  gl_Position = MVP * vec4(vpos, 1);

  float spriteDist;

  if (gl_Position.w == 0.0) {
    spriteDist = 0.00001;
  } else {
    spriteDist = gl_Position.w;
  }

  gl_PointSize =
      (((point_size * (g_Resolution.x / g_Resolution.y)) / spriteDist) *
       (g_Resolution.x / g_Resolution.y));

  particle_color = vcolor;
}