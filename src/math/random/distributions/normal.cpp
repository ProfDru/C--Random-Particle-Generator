#include <math/random/distributions/normal.h>

namespace rpg::math::random {
Normal::Normal(float mean, float standard_deviation)
    : dist(mean, standard_deviation) {}

float Normal::get_number(Generator& in) {
  return dist(in);
}

}  // namespace rpg::math::random