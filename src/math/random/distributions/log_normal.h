#pragma once

#include <math/random/distribution.h>
#include <random>
namespace rpg::math::random {
class LogNormal : public Distribution {
 private:
  std::lognormal_distribution<float> dist;

 public:
  LogNormal(float mean, float std);
  float get_number(Generator& in) override;
  ~LogNormal() {}
};
}  // namespace rpg::math::random