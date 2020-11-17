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
namespace rpg {

inline bool is_live_particle(const Particle& P) {
  return P.lifetime > 0;
}

inline bool is_dead_particle(const Particle& P) {
  return !(is_live_particle(P));
}

inline auto get_live_particles(std::vector<Particle>& particles,
                               int num_particles) {
  auto view = std::ranges::views::take(particles, num_particles);
  return std::ranges::filter_view(view, is_live_particle);
}
inline auto get_dead_particles(std::vector<Particle>& particles,
                               int num_particles) {
  auto view = std::ranges::views::take(particles, num_particles);
  return std::ranges::filter_view(view, is_dead_particle);
}

/*! \brief Creates a position array from an array of particles */
inline void CreatePositionArray(vector<Particle>& particles,
                                vector<float>& pos_arr) {
  int index = 0;
  std::ranges::for_each(get_live_particles(particles, pos_arr.size() / 3),
                        [&index, &pos_arr](const Particle& particle) {
                          const auto offset = index * 3;
                          pos_arr[offset] = particle.pos.x;
                          pos_arr[offset + 1] = particle.pos.y;
                          pos_arr[offset + 2] = particle.pos.z;
                          index++;
                        });
}

/*! \brief Creates a color array from an array of particles */
inline void CreateColorArray(vector<Particle>& particles,
                             vector<float>& color_arr) {
  int index = 0;
  std::ranges::for_each(get_live_particles(particles, color_arr.size() / 3),
                        [&index, &color_arr](const Particle& particle) {
                          const auto offset = index * 3;
                          color_arr[offset] = particle.color.x;
                          color_arr[offset + 1] = particle.color.y;
                          color_arr[offset + 2] = particle.color.z;
                          index++;
                        });
}

void UpdateParticle(Particle& P,
                    double time,
                    bool enable_bounce = true,
                    float coeff_of_restitution = 0.8,
                    float mass = 0.5) {
  P.lifetime -= time;
  // simulation::apply_gravity(P, time);
  simulation::update_particle_position(P, time);

  if (enable_bounce)
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
    P.color = this->start_color;
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

void ParticleEngine::emit_particle(int num_particles) {
  double i = 0;
  auto particles_to_replace = get_dead_particles(particles, max_particles) |
                              std::views::take(num_particles);
  std::ranges::for_each(particles_to_replace, [&i, this](Particle& P) {
    const double time = this->overflow + (i * this->fire_rate);
    P = simulation::fire_particle(
        this->magnitude.get_number(), this->vertical_angle.get_number(),
        this->particle_lifetime, this->horizontal_angle);

    UpdateParticle(P, time, this->bounce, this->coeff_of_restitution);
    color_particle(P);
    this->update_arrays(P, i + this->num_particles);
    i++;
  });
  this->num_particles += i;
}

void ParticleEngine::create_new_particles(double time) {
  const int num_shots = queued_shots(time);

  std::max(max_particles - static_cast<int>(particles.size()), 0);

  emit_particle(num_shots);
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
    particles.resize(max_particles,
                     Particle{glm::vec3(0, 0, 0), glm::vec3(0, 0, 0)});
    color_storage.resize(max_particles * 3);
    position_storage.resize(max_particles * 3);
  }

  int count = 0;
  std::ranges::for_each(get_live_particles(particles, max_particles),
                        [this, time, &count](Particle& p) {
                          UpdateParticle(p, time, bounce, coeff_of_restitution,
                                         horizontal_angle);
                          color_particle(p);
                          if (p.lifetime > 0)
                            update_arrays(p, count++);
                        });

  // Update our particle count
  this->num_particles = count;

  // Create new particles (They're updated implicitly)
  create_new_particles(time);
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

inline void ParticleEngine::update_arrays(Particle& P, int i) {
  const int offset = i * 3;
  color_storage[offset] = P.color.x;
  color_storage[offset + 1] = P.color.y;
  color_storage[offset + 2] = P.color.z;

  position_storage[offset] = P.pos.x;
  position_storage[offset + 1] = P.pos.y;
  position_storage[offset + 2] = P.pos.z;
}

}  // namespace rpg