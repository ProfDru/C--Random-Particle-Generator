#pragma once
#include <entities/entity.h>
#include <math\random\random_enums.h>
#include <entities\particle.h>
#include <random_or_constant.h>

#include <vector>
#include <string>

#include <glm/glm.hpp>

namespace rpg {

class ParticleEngine : public Entity {
  enum class COLOR_MODE { CONSTANT = 0, GRADIENT = 1, RAINBOW = 2 };
  enum class PARAMETER { LIFETIME = 0, DIST_FROM_GROUND = 1, VELOCITY = 2 };

 public:
  COLOR_MODE color_mode = COLOR_MODE::RAINBOW;
  PARAMETER color_param = PARAMETER::LIFETIME;
  /// PARTICLE
  float coeff_of_restitution = 0.8f;
  bool bounce = true;

  // EMITTER
  math::random::RNG_Algorithm random_algorithm =
      math::random::RNG_Algorithm::DEFAULT;
  int max_particles =
      1000000;  //< Maximum number of particles alive at any given time
  double fire_rate =
      0.001;  //< Minimum delay between the creation of each particle

 private:
  glm::vec3 pos = {0, 0, 0};
  std::vector<Particle> particles;
  double overflow = 0.0;
  double last_update = 0.0;
  const double update_threshold = 0.01 / 1000.0;
  std::vector<float> color_storage;
  std::vector<float> position_storage;
  int num_particles = 0;

  /*! \brief Create a enw particle */
  Particle gen_particle();

  /*! \brief Determine how many particles should be emitted based on the
   * firerate, time since last update, and number of alive particles. */
  int queued_shots(double time_since);

  /*! \brief Create and emit particles based on how much time passed.. */
  void create_new_particles(double time, int count);

  /*! \brief Emit as many particles as possible */
  void emit_particle(int num_particles);

  /*! \brief color particle by this particle engine's color mode. */
  void color_particle(Particle& P);

  /*! \brief color particle by this particle engine's color mode. */
  void color_particle(Particle& P, float min, float max);

  /*! \brief Resize and clear arrays if needed. */
  void resize_if_needed();

  /*! \brief Update a particle's position */
  void update_particle(Particle& P, double time);

  float get_particle_value(const Particle& P);

  /*! \brief Get the current color range depending on which color enums are
   * specified */
  std::array<float, 2> color_range();

  /*! \brief Apply simulation to every live particle, detect and remove dead
   * particles, and create new particles */
  void simulate_particles(double time);

  /*! Add this particle to the color and position arrays at index i. */
  void update_arrays(Particle& P);

 public:
  // EMITTER

  int particles_per_second = 200000;
  float particle_lifetime = 5.0f;  //< Maximum length of time a particle can be
                                   // alive before being cleaned up

  RandomOrConstant vertical_angle;  //= RandomOrConstant(20.0f, 0.0f, 90.0f);

  RandomOrConstant magnitude;  //< MAgnitude of the initial velocity vector  for
                               // each new particle.
  float horizontal_angle = 360.0f;

  // COLORS
  glm::vec3 start_color = glm::vec3{1, 1, 1};
  glm::vec3 end_color = glm::vec3{0, 0, 0};

  /*! \brief Construct the particle engine */
  ParticleEngine();

  /*! \brief Update all particles */
  void Update();

  const std::vector<float>& GetVertexBuffer();
  const std::vector<float>& GetColorBuffer();
  int NumVertices() const;
  int NumParticles() const;
  int MaxVertices() const;

  //~ParticleEngine();
};
}  // namespace rpg