#pragma once
#include <entities/entity.h>

#include <entities\particle.h>

#include <vector>
#include <string>

#include <glm/glm.hpp>

namespace rpg {

class ParticleEngine : public Entity {
  glm::vec3 pos = {0, 0, 0};
  std::vector<Particle> particles;

 public:
  int max_patricles = 10000;
  float particle_lifetime = 5.0f;
  float angle = 20.0f;

  /*! \brief Construct the particle engine */
  ParticleEngine();

  /*! \brief Update all particles */
  void Update();

  std::vector<float> GetVertexBuffer() const;
  std::vector<float> GetColorBuffer() const;
  int NumVertices() const;

  //~ParticleEngine();
};
}  // namespace rpg