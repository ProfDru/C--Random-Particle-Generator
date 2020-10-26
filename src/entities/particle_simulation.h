
#pragma once
#include <entities\particle.h>

#include <vector>
namespace rpg::simulation {

extern float time_scale;
void simulate_particles(std::vector<Particle>& P);

}  // namespace rpg::simulation