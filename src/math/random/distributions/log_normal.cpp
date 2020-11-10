#include <math/random/distributions/log_normal.h>

namespace rpg::math::random {
LogNormal::LogNormal(float mean, float std) : dist(mean, std) {}

float LogNormal::get_number(Generator& in) {
  return dist(in);
}

}  // namespace rpg::math::random