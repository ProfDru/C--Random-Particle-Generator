
#pragma once
#include <entities\particle.h>
#include <math/random/random_enums.h>
#include <vector>
namespace rpg::simulation {

extern float time_scale;

void update_particle_position(Particle& P, double time);

double get_time_since(double last_time);

double get_time();

void simple_ground_bounce(Particle& P,
                          float ground_height,
                          float e,
                          double time);

Particle fire_particle(float magnitude,
                       float vertical_angle,
                       float lifetime,
                       float max_hoizontal_angle);

}  // namespace rpg::simulation