#pragma once
#include <math/random/distribution.h>
#include <random>

namespace rpg::math::random {

class Normal : public Distribution {
 private:
  float mean, standard_deviation;
  std::normal_distribution<float> dist;

 public:
  Normal(float mean, float standard_deviation);

  float get_number(Generator& in) override;

  ~Normal(){};
};
}  // namespace rpg::math::random