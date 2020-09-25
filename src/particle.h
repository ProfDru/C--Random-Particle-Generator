#include <glm/glm.hpp>

namespace rpg {
struct Particle {
  glm::vec3 pos;
  glm::vec3 velocity;
  glm::vec3 color;
  float lifetime;

  Particle(glm::vec3 pos, glm::vec3 color);
};
}  // namespace rpg