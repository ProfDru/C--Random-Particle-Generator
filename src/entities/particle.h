#pragma once
#include <glm/glm.hpp>

namespace rpg {
struct Particle {
  glm::vec3 pos = glm::vec3(0, 0, 0);
  glm::vec3 velocity = glm::vec3(0, 0, 0);
  glm::vec3 color = glm::vec3(0, 0, 0);
  float lifetime = -1.0f;

  Particle();
  Particle(glm::vec3 pos, glm::vec3 color);
};
}  // namespace rpg