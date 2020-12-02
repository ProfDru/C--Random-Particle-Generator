#pragma once
#include <glm/glm.hpp>
#include <entities/particle.h>

namespace rpg::simulation {
void rainbow_by_lifetime(Particle& P, float max_lifetime);

/*! \brief Determine how far val is between min/max then use that as a hue value
 * on a HSV scale.*/
std::array<float, 3> rainbow_by_param(float min, float max, float val);

glm::vec3 lerp_by_param(float min,
                        float max,
                        float val,
                        const glm::vec3& color1,
                        const glm::vec3& color2);
}  // namespace rpg::simulation