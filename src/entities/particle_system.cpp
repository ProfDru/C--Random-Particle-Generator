#include <entities\particle_system.h>
#include <entities\particle_simulation.h>
#include <entities\particle_color_algs.h>

#include <functional>
#include <cassert>
#include <math.h>
#include <assert.h>
#include <math.h>

using std::vector;
namespace rpg {

/*! \brief Creates a position array from an array of particles */
inline vector<float> CreatePositionArray(const vector<Particle>& particles) {
  std::vector<float> pos_arr(particles.size() * 3);
  for (long long unsigned int i = 0; i < particles.size(); i++) {
    const auto offset = i * 3;
    const Particle& particle = particles[i];
    pos_arr[offset] = particle.pos.x;
    pos_arr[offset + 1] = particle.pos.y;
    pos_arr[offset + 2] = particle.pos.z;
  }

  return pos_arr;
}

/*! \brief Creates a color array from an array of particles */
inline vector<float> CreateColorArray(const vector<Particle>& particles) {
  std::vector<float> color_arr(particles.size() * 3);

  for (long long unsigned int i = 0; i < particles.size(); i++) {
    const auto offset = i * 3;
    const Particle& particle = particles[i];
    color_arr[offset] = particle.color.r;
    color_arr[offset + 1] = particle.color.g;
    color_arr[offset + 2] = particle.color.b;
  }

  return color_arr;
}

void UpdateParticle(Particle& P,
                    float time,
                    bool enable_bounce = true,
                    float coeff_of_restitution = 0.8,
                    float mass = 0.5) {
  P.lifetime -= time;
  simulation::apply_gravity(P, time);
  simulation::update_particle_position(P, time);

  if (enable_bounce)
    simulation::simple_ground_bounce(P, 0, coeff_of_restitution, time);
}

int ParticleEngine::queued_shots(float time_since) {
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
  return magnitude * std::sin(angle);
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
        max = calculate_height(this->magnitude, this->angle);
        val = abs(P.velocity.y);
        break;
      case PARAMETER::DIST_FROM_GROUND:
        min = 0;
        max = find_apex(this->magnitude, this->angle);
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
  for (int i = 0; i < num_particles; i++) {
    // Simulate this particle for the time between it should have been
    // fired and the time it was fired
    const float sim_time =
        (static_cast<float>(i) * this->fire_rate) + this->overflow;

    if (sim_time >= this->particle_lifetime)
      break;

    Particle P = simulation::fire_particle(this->magnitude, this->angle,
                                           this->particle_lifetime);

    UpdateParticle(P, sim_time, true, this->coeff_of_restitution);
    color_particle(P);

    particles.push_back(P);
  }
}

void ParticleEngine::create_new_particles(float time) {
  if (NumVertices() >= max_particles)
    return;

  const int num_shots = queued_shots(time);

  // Limit max number of particles by max_particles and shot time
  const int remaining_vertices = std::max(max_particles - NumVertices(), 0);
  const int particle_budget = std::clamp(num_shots, 0, remaining_vertices);

  emit_particle(particle_budget);
}

ParticleEngine::ParticleEngine() {
  this->particles = std::vector<Particle>();
  last_update = simulation::get_time();
}

/*! \brief Remove dead particles from the particle system */
void remove_particles(std::vector<Particle>& particles) {
  particles.erase(
      std::remove_if(particles.begin(), particles.end(),
                     [](Particle& p) -> bool { return (p.lifetime <= 0); }),
      particles.end());
}

void ParticleEngine::simulate_particles(float time) {
  // Apply simulation step to all particles
  for (auto& p : particles) {
    UpdateParticle(p, time, this->bounce, this->coeff_of_restitution);
    color_particle(p);
  }

  // Remove dead particles
  remove_particles(this->particles);

  // Create new particles
  create_new_particles(time);
}

void ParticleEngine::Update() {
  // Get time
  float time = simulation::get_time_since(last_update) / 1000.0f;

  if (time > update_threshold) {
    // Step through physics in discreet steps
    const double max_time = 0.016;
    const int steps = floor(time / max_time);
    const double remainder = time - (steps * max_time);
    if (steps > 0)
      for (int i = 0; i < steps; i++)
        simulate_particles(max_time);

    simulate_particles(remainder);

    last_update = simulation::get_time();
  }
}

std::vector<float> ParticleEngine::GetVertexBuffer() const {
  return CreatePositionArray(particles);
}

std::vector<float> ParticleEngine::GetColorBuffer() const {
  return CreateColorArray(this->particles);
};

int ParticleEngine::NumVertices() const {
  return this->particles.size() * 3;
}

}  // namespace rpg