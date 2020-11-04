
#pragma once
#include <entities\particle.h>

#include <vector>
namespace rpg::simulation {

extern float time_scale;
void simulate_particles(std::vector<Particle>& P,
                        float max_particles,
                        float angle,
                        float lifetime,
                        float timescale = 1.0f);

void sim_particle(Particle& p, float time_diff);

void apply_gravity(Particle& P, float time);

void update_particle_position(Particle& P, double time);

double get_time_since(double last_time);

double get_time();

bool simple_ground_bounce(Particle& P,
                          float ground_height,
                          float e,
                          double time);

Particle fire_particle(float magnitude, float vertical_angle, float lifetime);

bool has_lifetime(const Particle& p);
}  // namespace rpg::simulation