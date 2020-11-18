
#include <entities\particle.h>

namespace rpg {

Particle::Particle(glm::vec3 pos, glm::vec3 color) {
  this->pos = pos;
  this->color = color;
  this->velocity = glm::vec3{0, 0, 0};
  this->lifetime = -1.0f;
}
}  // namespace rpg
