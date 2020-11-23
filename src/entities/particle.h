#pragma once
#include <glm/glm.hpp>

namespace rpg {
struct Particle {
  float lifetime = -1.0f;
  glm::vec3 pos = glm::vec3(0, 0, 0);
  glm::vec3 color = glm::vec3(0, 0, 0);
  glm::vec3 velocity = glm::vec3(0, 0, 0);

  Particle();
  Particle(glm::vec3 pos, glm::vec3 color);
};
}  // namespace rpg