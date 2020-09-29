
#include <sys_time.h>
#include <particle_simulation.h>
#include <random_manager.h>

#include <glm/gtx/polar_coordinates.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/color_space.hpp>

#include <algorithm>
#include <numbers>

namespace rpg::simulation {

static double last_time = 0;
static const float time_threshold = 0.001f;

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

  return return_time;
}

/*! \brief Acceperate a particle downward in accordance with the forces of
 * gravity */
void apply_gravity(Particle& p, float time) {
  p.velocity += (glm::vec3(0, -gravitational_constant, 0) * time);
}

/*! \brief Move particle based on it's velocity */
void update_particle_position(Particle& p, float time) {
  p.pos += (p.velocity * time);
  if (p.pos.y <= 0 && p.velocity.y < 0) {
    p.color = glm::mix(p.color, glm::vec3(0, 0, 0),
                       std::min(p.velocity.y / 3.0f, 1.0f));

    p.velocity.y *= -0.1;
    p.velocity.z *= 0.75;
    p.velocity.x *= 0.75;
    p.lifetime = std::min(p.lifetime, 0.25f);
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

  apply_gravity(p, time);
  update_particle_position(p, time);
  return true;
}

static float overflow = 0.0f;
const static float fire_rate = 0.001f;
static const int max_patricles = 50000;
static const float spread = 20.0f;

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

inline float get_rand(float min, float max) {
  return RandomManager::random_range(min, max);
}

inline float to_radians(float num_in_degrees) {
  return std::numbers::pi * num_in_degrees / 180.0f;
}

inline Particle EmitParticle() {
  const float magnitude = get_rand(min_mag, max_mag);
  const float mag_intensity =
      ((abs(magnitude) - min_mag) / (max_mag - min_mag));

  const float mag_spread = spread * mag_intensity;
  const float horizontal_angle = get_rand(-mag_spread, mag_spread);
  const float vertical_angle = get_rand(-mag_spread, mag_spread);

  glm::vec2 polar_coords(to_radians(horizontal_angle),
                         to_radians(vertical_angle));
  glm::vec3 dir = glm::euclidean(polar_coords);
  dir = glm::rotateX(dir, to_radians(-90));

  Particle out_particle(origin, white);
  out_particle.velocity = (dir * magnitude);

  // float h = mag_intensity * 255.0f;
  // float s = 1.0f;
  // float v = 1.0f;
  // glm::vec3 hsv(h, s, v);
  // out_particle.color = glm::rgbColor(hsv);

  out_particle.color =
      glm::mix(glm::vec3(1, 1, 1), glm::vec3(0, 0, 1), mag_intensity);

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
  const double time_diff = static_cast<double>(get_time_since()) / 1000.0;

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