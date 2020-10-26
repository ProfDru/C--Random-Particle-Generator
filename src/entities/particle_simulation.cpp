
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

static double last_time = 0;
static const float time_threshold = 0.00001f;
static const float start_lifetime = 5.0f;
float time_scale = 1.0f;

double get_time_since() {
  // Get the current time
  double current_time = rpg::system::get_precise_time_ms();

  // If last time was never set, just return 0 and set it
  if (last_time == 0) {
    last_time = current_time;
    return 0;
  }

  // set the return value then update last time
  auto return_time = current_time - last_time;
  last_time = current_time;

  return return_time * time_scale;
}

inline float get_rand(float min, float max) {
  return RandomManager::random_range(min, max);
}

inline float get_rand_nolimits() {
  return RandomManager::GetRandomNumber();
}

/*! \brief Move particle based on it's velocity */
void update_particle_position(Particle& p, float time) {
  physics::apply_velocity(p, time);

  if (p.pos.y <= 0 && p.velocity.y < 0) {
    physics::bounce_basic(p, 5.0, 0.85f);
    // p.lifetime -= 1.0f;

    // math::inverse_lerp(0.25, 2.0, math::magnitude(p.velocity));

    /*
        if (abs(p.velocity.y) < 4.0f)
          p.lifetime = 0;
        else
          p.lifetime += 3.0f;
    */
  }
}

/*! \brief Determine if this particle should die on this frame */
bool has_lifetime(const Particle& p) {
  return p.lifetime > 0.0f;
}

bool sim_particle(Particle& p, float time) {
  if (!has_lifetime(p))
    return false;

  p.lifetime -= time;

  double life_left = 1.0 - math::inverse_lerp(0.0, start_lifetime, p.lifetime);
  p.color = glm::rgbColor(glm::vec3(life_left * 255, 1.0f, 1 - life_left));
  physics::apply_gravity(p, time);
  update_particle_position(p, time);
  return true;
}

static float overflow = 0.0f;
const static float fire_rate = 0.0005f;
static const int max_patricles = 50000;
static const float spread = 45.0f;

const float max_mag = 3.0f;
const float min_mag = 1.0f;
const glm::vec3 origin(0, 0, 0);
const glm::vec3 white(255, 255, 255);

inline glm::vec3 make_random_color() {
  float saturation = RandomManager::random_range(0, 255);

  return glm::rgbColor(glm::vec3(saturation, 0.25f, 1.0f));
}

/*! \brief calculate the number of new particles to create this frame */
int calc_num_shots(float time_since) {
  const float shot_time = overflow + time_since;

  int shots = std::floor(shot_time / fire_rate);
  if (shots > 0)
    overflow = (shot_time - (static_cast<float>(shots) * fire_rate));
  else
    overflow += time_since;

  return shots;
}

inline Particle EmitParticle() {
  const float magnitude = get_rand(12.5, 15);  // get_rand(min_mag, max_mag);

  const float horizontal_angle =
      get_rand(0, 360);               // rand(0, 360);
                                      // ticks = (ticks % 360) + 1;
  const float vertical_angle = 25.0;  // get_rand(0, spread);

  auto dir = math::spherical_to_cartesian(glm::vec3(
      1, math::to_radians(horizontal_angle), math::to_radians(vertical_angle)));
  dir = glm::rotateX(dir, math::to_radians<int, float>(-90));

  Particle out_particle(origin, white);
  out_particle.velocity = (dir * magnitude);

  out_particle.color = {0, 0.25, 1};
  out_particle.lifetime = start_lifetime;
  return out_particle;
}

void create_particles(std::vector<Particle>& particles, float time) {
  const int num_shots = calc_num_shots(time);

  int particle_budget =
      std::min(max_patricles - static_cast<int>(particles.size()), num_shots);

  if (particle_budget > 0)
    for (int i = 0; i < particle_budget; i++) {
      particles.push_back(EmitParticle());
    }
}

void simulate_particles(std::vector<Particle>& particles) {
  // Convert milliseconds to seconds
  const float time_diff = static_cast<float>(get_time_since()) / 1000.0f;

  // Don't update if the time is less than the threshold
  if (time_diff < time_threshold)
    return;

  particles.erase(std::remove_if(particles.begin(), particles.end(),
                                 [time_diff](Particle& p) -> bool {
                                   return !sim_particle(p, time_diff);
                                 }),
                  particles.end());

  create_particles(particles, time_diff);
}

}  // namespace rpg::simulation