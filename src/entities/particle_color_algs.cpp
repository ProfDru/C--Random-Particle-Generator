#include <entities/particle_color_algs.h>

#include <math/base.h>
#include <math/color.h>
#include <math.h>

namespace rpg::simulation {
void rainbow_by_lifetime(Particle& P, float max_lifetime) {
  float percentage_of_life_time =
      rpg::math::inverse_lerp(0.0, max_lifetime, P.lifetime);

  P.color.r = percentage_of_life_time;
  P.color.g = 1.0;
  P.color.b = 1.0;

  rpg::math::color::hsv_to_rgb(P.color);
}

}  // namespace rpg::simulation