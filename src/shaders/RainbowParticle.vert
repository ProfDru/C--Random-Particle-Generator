#version 440 core

// Input vertex data. Only position and color for now.
layout(location = 0) in vec3 vpos;
layout(location = 1) in vec3 vcolor;

// Output data. Only color for now. We'll change position by setting
// gl_position.
out vec3 particle_color;

// Constants. ModelViewProjection Matrix
uniform mat4 MVP;

// All components are in the range [0…1], including hue.
vec3 hsv2rgb(vec3 c) {
  vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
  vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
  return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec3 clamp_vector(vec3 vec) {
  return vec3(clamp(vec.x, 0.1, 0.9), clamp(vec.y, 0.1, 0.9),
              clamp(vec.z, 0.1, 0.9));
}

void main() {
  // Output position of the vertex, in clip space : MVP * position
  gl_Position = MVP * vec4(vpos, 1);

  // UV of the vertex. No special space for this one.
  // particle_color = vcolor;
  float distance_to_origin =
      clamp(distance(vec3(0.0, 0.0, 0.0), vpos) / 10.0, 0.01, 0.9);

  vec3 dist_color = hsv2rgb(vec3(distance_to_origin, 1.0, 1.0));
  vec3 clamped_color = clamp_vector(dist_color);
  vec3 v_copy = vcolor;

  v_copy = v_copy - vec3(255, 255, 255);
  v_copy = v_copy + clamped_color;
  particle_color = v_copy;
}