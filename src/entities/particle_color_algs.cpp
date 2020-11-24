#include <entities/particle_color_algs.h>

#include <glm/glm.hpp>

#include <math/base.h>
#include <math/color.h>
#include <math.h>

namespace rpg::simulation {
void rainbow_by_lifetime(Particle& P, float max_lifetime) {
  P.set_color(rainbow_by_param(0, max_lifetime, P.lifetime));
}

glm::vec3 rainbow_by_param(double min, double max, double val) {
  const double violet_cutoff = 0.3;

  // Add red_cutoff to the hue to ensure it isn't in red if it's near zero
  double hue = rpg::math::inverse_lerp(min, max, val);

  const double capped_hue = 1.0 - std::lerp(violet_cutoff, 1.0, hue);
  const double clamped_hue = std::clamp(capped_hue, 0.0, 1.0);

  glm::vec3 return_color = glm::vec3{clamped_hue, 1.0, 1.0};
  rpg::math::color::hsv_to_rgb(return_color);

  return return_color;
}

glm::vec3 lerp_by_param(double min,
                        double max,
                        double val,
                        const glm::vec3& color1,
                        const glm::vec3& color2) {
  const double dist = rpg::math::inverse_lerp(min, max, val);

  return glm::mix(color2, color1, dist);
}

}  // namespace rpg::simulation