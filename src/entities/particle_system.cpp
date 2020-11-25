#include <entities\particle_system.h>
#include <entities\particle_simulation.h>
#include <entities\particle_color_algs.h>

#include <functional>
#include <cassert>
#include <cmath>
#include <assert.h>
#include <math.h>
#include <numbers>
#include <ranges>
#include <algorithm>
#include <concepts>

using std::vector;
using namespace std::ranges;
namespace rpg {

inline bool is_live_particle(const Particle& P) {
  return P.lifetime > 0.0f;
}
inline bool is_dead_particle(const Particle& P) {
  return !(is_live_particle(P));
}

inline void ParticleEngine::update_particle(Particle& P, float time) {
  P.lifetime -= time;
  // simulation::apply_gravity(P, time);
  simulation::update_particle_position(P, time);

  if (bounce)
    simulation::simple_ground_bounce(P, 0, coeff_of_restitution, time);
}

int ParticleEngine::queued_shots(double time_since) {
  // Use overflow from the previous shot queue
  const double shot_time = this->overflow + time_since;

  // Calculate the maximum number of shots we can fire in the amount of time
  // since our firerate
  int shots = std::floor(shot_time / fire_rate);

  if (shots > 0)
    overflow = (shot_time - (static_cast<double>(shots) * fire_rate));
  else
    overflow += time_since;

  return shots;
}

inline double calculate_height(double magnitude, double angle) {
  return abs(magnitude * std::sin(std::numbers::pi * (90.0 - angle) / 180.0));
}

inline float find_apex(float magnitude, float angle) {
  const double y_component = calculate_height(magnitude, angle);

  double apex_time = y_component / 9.8;

  return y_component * apex_time + (-9.8 * pow(apex_time, 2) / 2);
}

inline std::array<float, 2> ParticleEngine::color_range() {
  float min, max;
  switch (color_param) {
    case PARAMETER::LIFETIME:
      min = 0;
      max = particle_lifetime;
      break;
    case PARAMETER::VELOCITY:
      min = 0;
      max = calculate_height(magnitude.constant, vertical_angle.constant);
      break;
    case PARAMETER::DIST_FROM_GROUND:
      min = 0;
      max = find_apex(magnitude.constant, vertical_angle.constant);
      break;
    default:
      min = 0;
      max = 1;
      break;
  }
  return std::array<float, 2>{min, max};
}

inline double ParticleEngine::get_particle_value(const Particle& P) {
  switch (color_param) {
    case PARAMETER::LIFETIME:
      return P.lifetime;
      break;
    case PARAMETER::VELOCITY:
      return abs(P.velocity[1]);
      break;
    case PARAMETER::DIST_FROM_GROUND:
      return P.pos[1];
      break;
  }
  return 0.0;
}

inline void ParticleEngine::color_particle(Particle& P, float min, float max) {
  if (color_mode == COLOR_MODE::CONSTANT)
    return;

  const float val = get_particle_value(P);

  if (color_mode == COLOR_MODE::RAINBOW)
    P.set_color(simulation::rainbow_by_param(min, max, val));
  else if (color_mode == COLOR_MODE::GRADIENT)
    P.set_color(
        simulation::lerp_by_param(min, max, val, start_color, end_color));
}

void ParticleEngine::color_particle(Particle& P) {
  if (this->color_mode == COLOR_MODE::CONSTANT) {
    return;
  } else {
    const auto min_max = color_range();
    color_particle(P, min_max[0], min_max[1]);
  }
}

void ParticleEngine::emit_particle(int queued_shots) {
  double i = 0;

  // Get all dead particles
  auto particles_to_replace =
      particles | views::filter(is_dead_particle) | views::take(queued_shots);

  // For each queued shot, create a new particle to replace a dead particle
  for_each(particles_to_replace, [&i, this](Particle& P) {
    const double time = this->overflow + (i * this->fire_rate);

    P = simulation::fire_particle(
        this->magnitude.get_number(), this->vertical_angle.get_number(),
        this->particle_lifetime, this->horizontal_angle);

    P.set_color(start_color);
    update_particle(P, time);
    color_particle(P);

    this->update_arrays(P);
    i += 1;
  });
}

void ParticleEngine::create_new_particles(double time, int count) {
  const int num_shots = queued_shots(time);
  const int max_particles_per_frame = particle_lifetime / fire_rate;
  const int particles_remaining = std::max(max_particles - num_particles, 0);
  const int particle_budget = std::min(std::min(num_shots, particles_remaining),
                                       max_particles_per_frame);
  if (particle_budget > 0)
    emit_particle(particle_budget);
}

ParticleEngine::ParticleEngine()
    : vertical_angle(20.0f, 0.0f, 90.0f),
      magnitude(10.0f, 0.0f, 20.0f),
      position_storage(10000),
      color_storage(10000) {
  this->particles = std::vector<Particle>();
  last_update = simulation::get_time();
}

/*! \brief Remove dead particles from the particle system */
void remove_particles(std::vector<Particle>& particles) {
  particles.erase(
      std::remove_if(particles.begin(), particles.end(),
                     [](Particle& p) -> bool { return (p.lifetime <= 0.0f); }),
      particles.end());
}

inline void ParticleEngine::resize_if_needed() {
  // Resize particle array if needed
  if (particles.size() != max_particles) {
    particles.clear();
    color_storage.clear();
    position_storage.clear();

    particles.resize(max_particles);
    color_storage.resize(max_particles * 3);
    position_storage.resize(max_particles * 3);
    num_particles = 0;
  }
}

void ParticleEngine::simulate_particles(double time) {
  // Apply simulation step to all particles
  resize_if_needed();

  // Note, here we take num_particles -1. Not sure why this is necessary,
  // however if we don't then it's a full array scan to perform this operation.
  auto currently_live_particles = particles | views::filter(is_live_particle) |
                                  views::take(num_particles - 1);

  // Get the minimum and maximum values for colors
  const auto min_max = color_range();
  const float min = min_max[0];
  const float max = min_max[1];
  const float float_time = static_cast<float>(time);
  num_particles = 0;
  // iterate through each living particle and update it
  for_each(currently_live_particles, [this, float_time, min, max](Particle& p) {
    update_particle(p, float_time);
    color_particle(p, min, max);
    // if the particle is still alive add it to our storage arrays
    if (is_live_particle(p))
      update_arrays(p);
  });
  num_particles++;

  // Create new particles based on firerate
  create_new_particles(time, num_particles);
}

void ParticleEngine::Update() {
  // Update firerate and get the current time
  fire_rate = 1.0 / static_cast<double>(particles_per_second);
  const double time = simulation::get_time_since(last_update) / 1000.0;

  // If the time is within our update threshold, simulate particles, then
  // update our last_update time
  // if (time > (simulation::time_scale * update_threshold)) {
  const double this_update = simulation::get_time();
  simulate_particles(time);
  last_update = this_update;
  //}
}

const std::vector<float>& ParticleEngine::GetColorBuffer() {
  return color_storage;
}

const std::vector<float>& ParticleEngine::GetVertexBuffer() {
  return position_storage;
};

int ParticleEngine::NumVertices() const {
  return NumParticles() * 3;
}

int ParticleEngine::NumParticles() const {
  return num_particles;
}

inline void ParticleEngine::update_arrays(Particle& P) {
  const int offset = num_particles * 3;
  const auto color = P.color;
  color_storage[offset] = color[0];
  color_storage[offset + 1] = color[1];
  color_storage[offset + 2] = color[2];

  const auto position = P.pos;
  position_storage[offset] = position[0];
  position_storage[offset + 1] = position[1];
  position_storage[offset + 2] = position[2];
  ++num_particles;
}

int ParticleEngine::MaxVertices() const {
  return max_particles * 3;
}

}  // namespace rpg