#include <entities\particle_system.h>
#include <entities\particle_simulation.h>
#include <entities\particle_color_algs.h>

#include <functional>
#include <cassert>
#include <math.h>
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
  return P.lifetime > 0;
}
inline bool is_dead_particle(const Particle& P) {
  return !(is_live_particle(P));
}

inline void ParticleEngine::update_particle(Particle& P, double time) {
  P.lifetime -= time;
  // simulation::apply_gravity(P, time);
  simulation::update_particle_position(P, time);

  if (bounce)
    simulation::simple_ground_bounce(P, 0, coeff_of_restitution, time);

  color_particle(P);
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

inline float calculate_height(float magnitude, float angle) {
  return abs(magnitude * std::sin(std::numbers::pi * (90.0 - angle) / 180.0));
}

inline float find_apex(float magnitude, float angle) {
  const float y_component = calculate_height(magnitude, angle);

  float apex_time = y_component / 9.8;

  return y_component * apex_time + (-9.8 * pow(apex_time, 2) / 2);
}

void ParticleEngine::color_particle(Particle& P) {
  if (this->color_mode == COLOR_MODE::CONSTANT) {
    return;
  } else {
    // Determine the parameters needed for lerp
    float min, max, val;
    switch (this->color_param) {
      case PARAMETER::LIFETIME:
        min = 0;
        max = this->particle_lifetime;
        val = P.lifetime;
        break;
      case PARAMETER::VELOCITY:
        min = 0;
        max = calculate_height(this->magnitude.constant,
                               this->vertical_angle.constant);
        val = abs(P.velocity.y);
        break;
      case PARAMETER::DIST_FROM_GROUND:
        min = 0;
        max =
            find_apex(this->magnitude.constant, this->vertical_angle.constant);
        val = P.pos.y;
        break;
      default:
        min = 0;
        max = 1;
        val = 0;

        break;
    }

    // Apply lerp color algorithm
    if (this->color_mode == COLOR_MODE::RAINBOW)
      P.color = simulation::rainbow_by_param(min, max, val);
    else if (this->color_mode == COLOR_MODE::GRADIENT)
      P.color = simulation::lerp_by_param(min, max, val, this->start_color,
                                          this->end_color);
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

    P.color = start_color;
    update_particle(P, time);

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

void ParticleEngine::simulate_particles(double time) {
  // Apply simulation step to all particles

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

  // Note, here we take num_particles -1. Not sure why this is necessary,
  // however if we don't then it's a full array scan to perform this operation.
  auto currently_live_particles = particles | views::filter(is_live_particle) |
                                  views::take(num_particles - 1);

  int count = 0;
  if (num_particles > 0) {
    num_particles = 0;
    // iterate through each living particle and update it
    for_each(currently_live_particles, [this, time, &count](Particle& p) {
      update_particle(p, time);

      // if the particle is still alive add it to our storage arrays
      if (is_live_particle(p))
        update_arrays(p);
    });
    num_particles++;
  }

  // Create new particles based on firerate
  create_new_particles(time, num_particles);
}

void ParticleEngine::Update() {
  // Update firerate and get the current time
  fire_rate = 1.0 / static_cast<double>(particles_per_second);
  const double time = simulation::get_time_since(last_update) / 1000.0;

  // If the time is within our update threshold, simulate particles, then
  // update our last_update time
  if (time > (simulation::time_scale * update_threshold)) {
    const double this_update = simulation::get_time();
    simulate_particles(time);
    last_update = this_update;
  }
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
  const int offset = this->num_particles * 3;
  color_storage[offset] = P.color.x;
  color_storage[offset + 1] = P.color.y;
  color_storage[offset + 2] = P.color.z;

  position_storage[offset] = P.pos.x;
  position_storage[offset + 1] = P.pos.y;
  position_storage[offset + 2] = P.pos.z;
  this->num_particles += 1;
}

int ParticleEngine::MaxVertices() const {
  return max_particles * 3;
}

}  // namespace rpg