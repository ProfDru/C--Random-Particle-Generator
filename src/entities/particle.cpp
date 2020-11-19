
#include <entities\particle.h>

namespace rpg {

Particle::Particle(glm::vec3 pos, glm::vec3 color)
    : pos(pos), color(color), velocity(0, 0, 0), lifetime(-1.0f) {}

Particle::Particle()
    : pos(glm::vec3(0, 0, 0)),
      color(glm::vec3(0, 0, 0)),
      velocity(glm::vec3(0, 0, 0)),
      lifetime(-1.0f) {}
}  // namespace rpg
