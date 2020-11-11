#pragma once

#include <math/random/distribution.h>
#include <random>

namespace rpg::math::random {

template <typename dist_t>
class TMPDistribution : public Distribution {
  dist_t dist;

 public:
  inline TMPDistribution(float param_a, float param_b)
      : dist(param_a, param_b) {}
  inline float get_number(Generator& in) override { return dist(in); }
  ~TMPDistribution(){};
};
}  // namespace rpg::math::random