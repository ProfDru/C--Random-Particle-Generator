#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
namespace rpg {
struct Particle {
  glm::vec3 pos;
  glm::vec3 velocity;
  glm::vec3 color;
  float lifetime;
};

class ParticleEngine {
  static const int stride = 3;
  static const bool normalized = false;

  // std::vector<Particle> particles;
  std::vector<glm::vec3> points;
  GLuint VBO;

 public:
  /*! \brief Construct the particle engine */
  ParticleEngine();

  /*! \brief Draw all particles, */
  void Draw();

  /*! \brief Update all particles */
  void Update();

  //~ParticleEngine();
};
}  // namespace rpg