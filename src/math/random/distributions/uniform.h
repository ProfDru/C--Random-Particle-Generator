#pragma once
#include <math/random/distribution.h>

namespace rpg::math::random {

class Uniform : public Distribution {
 private:
  std::uniform_real_distribution<float> uniform_dist;

 public:
  Uniform(float min = 0.0f, float max = 0.0f);
  float get_number(Generator& in) override;

  ~Uniform() {}
};

}  // namespace rpg::math::random