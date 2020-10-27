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
  float overflow = 0.0f;
  double last_update = 0.0;

  /*! \brief Determine how many particles should be emitted based on the
   * firerate. */
  int queued_shots(float time_since);

  /*! \brief Destroy dead particles from the scene */
  void collect_dead_particles();

  /*! \brief Emit as many particles as possible */
  void create_new_particles(float time);

  /*! \brief Emit as many particles as possible */
  void emit_particle(int num_particles);

 public:
  int max_particles = 10000;
  float particle_lifetime = 5.0f;
  float angle = 20.0f;
  float fire_rate = 0.001f;
  float magnitude = 10.0f;
  double update_threshold = 0.000001f;

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