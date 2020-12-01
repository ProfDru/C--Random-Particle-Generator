
#pragma once
#include <entities\particle.h>
#include <math/random/random_enums.h>
#include <vector>
namespace rpg::simulation {

extern float time_scale;

void update_particle_position(Particle& P, float time);

double get_time_since(double last_time);

double get_time();

void run_physics_simulation(Particle& P,
                            bool enable_bounce,
                            float ground_height,
                            float e,
                            float time);

Particle fire_particle(float magnitude,
                       float vertical_angle,
                       float lifetime,
                       float max_hoizontal_angle);

}  // namespace rpg::simulation