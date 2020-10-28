
#include <sys_time.h>
#include <entities\particle_simulation.h>
#include <random_manager.h>

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
  return RandomManager::random_range(min, max);
}

inline float get_rand_nolimits() {
  return RandomManager::GetRandomNumber();
}

void apply_gravity(Particle& P, float time) {
  physics::apply_gravity(P, time);
}

/*! \brief Move particle based on it's velocity */
void update_particle_position(Particle& p, float time) {
  physics::apply_velocity(p, time);

  if (p.pos.y <= 0 && p.velocity.y < 0) {
    physics::bounce_basic(p, 5.0, 0.85, 0);
  }
}

/*! \brief Determine if this particle should die on this frame */
bool has_lifetime(const Particle& p) {
  return p.lifetime > 0.0f;
}

void update_position(Particle& p, float time) {
  physics::apply_gravity(p, time);
  update_particle_position(p, time);
}

const float max_mag = 3.0f;
const float min_mag = 1.0f;
const glm::vec3 origin(0, 0, 0);
const glm::vec3 white(255, 255, 255);

inline glm::vec3 make_random_color() {
  float saturation = RandomManager::random_range(0, 255);

  return glm::rgbColor(glm::vec3(saturation, 0.25f, 1.0f));
}

inline Particle EmitParticle(float angle, float lifetime) {
  const float magnitude = get_rand(12.5, 15);  // get_rand(min_mag, max_mag);

  const float horizontal_angle =
      get_rand(0, 360);                // rand(0, 360);
                                       // ticks = (ticks % 360) + 1;
  const float vertical_angle = angle;  // get_rand(0, spread);

  auto dir = math::spherical_to_cartesian(glm::vec3(
      1, math::to_radians(horizontal_angle), math::to_radians(vertical_angle)));
  dir = glm::rotateX(dir, math::to_radians<int, float>(-90));

  Particle out_particle(origin, white);
  out_particle.velocity = (dir * magnitude);

  out_particle.color = {0, 0.25, 1};
  out_particle.lifetime = lifetime;
  return out_particle;
}

Particle fire_particle(float magnitude, float vertical_angle, float lifetime) {
  const float horizontal_angle =
      get_rand(0, 360);  // rand(0, 360);
                         // ticks = (ticks % 360) + 1;

  auto dir = math::spherical_to_cartesian(glm::vec3(
      1, math::to_radians(horizontal_angle), math::to_radians(vertical_angle)));
  dir = glm::rotateX(dir, math::to_radians<int, float>(-90));

  Particle out_particle(origin, white);
  out_particle.velocity = (dir * magnitude);
  out_particle.color = {0, 0.25, 1};
  out_particle.lifetime = lifetime;
  return out_particle;
}

}  // namespace rpg::simulation