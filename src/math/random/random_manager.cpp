#include <math/random/random_manager.h>
#include <math/random/distributions/uniform.h>

#include <cmath>
#include <algorithm>

namespace rpg::math::random {
Generator GlobalRandom::rand_gen(RNG_Algorithm::DEFAULT);
std::unique_ptr<Distribution> GlobalRandom::dist =
    std::unique_ptr<Distribution>(new Uniform(0, 1));

float GlobalRandom::GetRandomNumber() {
  return dist->get_number(rand_gen);
}

float GlobalRandom::GetRandomNumber(float min, float max) {
  const float random_number = GlobalRandom::GetRandomNumber();
  return std::lerp(min, max, random_number);
}

}  // namespace rpg::math::random