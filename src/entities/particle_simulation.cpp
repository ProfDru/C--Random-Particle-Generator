
#include <sys_time.h>
#include <entities\particle_simulation.h>
#include <math/random/random_manager.h>

#include <math/base.h>
#include <math/vector3d.h>
#include <math/units.h>

#include <physics/rigid_body.h>

#include <glm/gtx/polar_coordinates.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/color_space.hpp>

#include <algorithm>
#include <numbers>

using namespace rpg::math::random;
namespace rpg::simulation {

float time_scale = 1.0f;

double get_time_since(double last_time) {
  const double current_time = get_time();

  // If last time was never set, just return 0 and set it
  if (last_time == 0) {
    last_time = current_time;
    return 0;
  }

  // set the return value then update last time
  const double return_time = current_time - static_cast<double>(last_time);

  return return_time * static_cast<double>(time_scale);
}

double get_time() {
  return rpg::system::get_precise_time_ms();
}

inline float get_rand(float min, float max) {
  return GlobalRandom::GetRandomNumber(min, max);
}

inline float get_rand_nolimits() {
  return GlobalRandom::GetRandomNumber();
}

/*! \brief Move particle based on it's velocity */
void update_particle_position(Particle& p, float time) {
  // physics::update_position_with_gravity(p.pos, p.velocity, time);
}

void run_physics_simulation(Particle& p,
                            bool enable_bounce,
                            float ground_height,
                            float e,
                            float time_since_last_update) {
  physics::full_simulation_step(p, enable_bounce, 0.5f, e, 0.0f,
                                time_since_last_update);
}

const glm::vec3 origin(0, 0, 0);
const glm::vec3 white(255, 255, 255);

Particle fire_particle(float magnitude,
                       float vertical_angle,
                       float lifetime,
                       float max_horizontal_angle) {
  const double horizontal_angle = get_rand(0, max_horizontal_angle);
  static const float rotation = math::to_radians<int, float>(-90);

  glm::vec3 dir = math::spherical_to_cartesian(glm::vec3(
      1, math::to_radians(horizontal_angle), math::to_radians(vertical_angle)));
  dir = glm::rotateX(dir, rotation);

  Particle out_particle;
  out_particle.set_velocity(dir * magnitude);
  out_particle.lifetime = lifetime;
  return out_particle;
}

}  // namespace rpg::simulation