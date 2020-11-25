#include <entities/particle_color_algs.h>

#include <glm/glm.hpp>

#include <math/base.h>
#include <math/color.h>
#include <math.h>

namespace rpg::simulation {
void rainbow_by_lifetime(Particle& P, float max_lifetime) {
  P.set_color(rainbow_by_param(0, max_lifetime, P.lifetime));
}

std::array<float, 3> rainbow_by_param(float min, float max, float val) {
  const float violet_cutoff = 0.3f;

  // Add red_cutoff to the hue to ensure it isn't in red if it's near zero
  float hue = rpg::math::inverse_lerp(min, max, val);

  const float capped_hue = 1.0f - std::lerp(violet_cutoff, 1.0f, hue);
  const float clamped_hue = std::clamp(capped_hue, 0.0f, 1.0f);

  std::array<float, 3> return_color{clamped_hue, 1.0f, 1.0f};
  rpg::math::color::hsv_to_rgb(return_color);

  return return_color;
}

glm::vec3 lerp_by_param(float min,
                        float max,
                        float val,
                        const glm::vec3& color1,
                        const glm::vec3& color2) {
  const float dist = rpg::math::inverse_lerp(min, max, val);

  return glm::mix(color2, color1, dist);
}

}  // namespace rpg::simulation