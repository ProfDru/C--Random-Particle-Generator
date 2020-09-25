#include <particle_simulation.h>
#include <random_manager.h>

#include <glm/gtx/polar_coordinates.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <chrono>
#include <algorithm>
#include <numbers>

namespace rpg::simulation {

// All of this time stuff should be moved to its own class
using clock = std::chrono::high_resolution_clock;
using timems = std::chrono::time_point<clock>;
static timems last_time;

static const float time_threshold = 0.01f;

int get_time_since() {
  timems current_time = clock::now();

  // If last time was never set, just return 0 and set it
  if (last_time.time_since_epoch().count() == 0) {
    last_time = current_time;
    return 0;
  }

  std::chrono::duration<float, std::milli> dur(current_time - last_time);
  last_time = current_time;
  return std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
}

/*! \brief Acceperate a particle downward in accordance with the forces of
 * gravity */
void apply_gravity(Particle& p, float time) {
  p.velocity += (glm::vec3(0, -gravitational_constant, 0) * time);
}

/*! \brief Move particle based on it's velocity */
void update_particle_position(Particle& p, float time) {
  p.pos += (p.velocity * time);
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
const static float fire_rate = 0.01f;
static const int max_patricles = 10000;
static const float spread = 10.0f;

const float max_mag = 2.0f;
const float min_mag = 1.0f;
const glm::vec3 origin(0, 0, 0);
const glm::vec3 white(255, 255, 255);

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
  const float horizontal_angle = get_rand(-spread, spread);
  const float vertical_angle = get_rand(-spread, spread);
  const float magnitude = get_rand(min_mag, max_mag);

  glm::vec2 polar_coords(to_radians(horizontal_angle),
                         to_radians(vertical_angle));
  glm::vec3 dir = glm::euclidean(polar_coords);
  dir = glm::rotateX(dir, to_radians(-90));

  Particle out_particle(origin, white);
  out_particle.velocity = (dir * magnitude);

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