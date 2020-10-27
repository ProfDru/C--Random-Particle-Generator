
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

}  // namespace rpg::simulation