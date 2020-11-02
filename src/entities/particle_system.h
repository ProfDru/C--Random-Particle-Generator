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
  double overflow = 0.0;
  double last_update = 0.0;
  double update_threshold = 0.00000001;

  /*! \brief Determine how many particles should be emitted based on the
   * firerate, time since last update, and number of alive particles. */
  int queued_shots(float time_since);

  /*! \brief Create and emit particles based on how much time passed.. */
  void create_new_particles(float time);

  /*! \brief Emit as many particles as possible */
  void emit_particle(int num_particles);

  /*! \brief Apply simulation to every live particle, detect and remove dead
   * particles, and create new particles */
  void simulate_particles(float time);

 public:
  // EMITTER
  int max_particles =
      15000;  //< Maximum number of particles alive at any given time
  float fire_rate =
      0.001;  //< Minimum delay between the creation of each particle
  float particle_lifetime = 5.0f;  //< Maximum length of time a particle can be
                                   // alive before being cleaned up
  float angle = 20.0f;  //< Angle between y+ and the ground to fire particles in
  float magnitude = 10.0f;  //< MAgnitude of the initial velocity vector  for
                            // each new particle.

  /// PARTICLE
  float coeff_of_restitution = 0.8f;

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