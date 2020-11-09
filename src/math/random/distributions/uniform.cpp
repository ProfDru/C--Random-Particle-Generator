#include <math/random/distributions/uniform.h>

namespace rpg::math::random {
Uniform::Uniform(float min, float max) : uniform_dist(min, max) {}

float Uniform::get_number(Generator& in) {
  return uniform_dist(in);
}
}  // namespace rpg::math::random