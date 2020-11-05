#include <math/random/random_manager.h>
#include <cmath>
#include <algorithm>

namespace rpg::math::random {

RandomNumberEngine<std::mt19937> RandomManager::mnt(RandomManager::RD);
RandomNumberEngine<std::minstd_rand> RandomManager::minstd(RandomManager::RD);
RandomNumberEngine<std::ranlux48> RandomManager::ranlux(RandomManager::RD);
RandomNumberEngine<std::ranlux48_base> RandomManager::ranlux_base(
    RandomManager::RD);
RandomNumberEngine<std::knuth_b> RandomManager::knuth_base(RandomManager::RD);
RandomNumberEngine<std::default_random_engine> RandomManager::default_engine(
    RandomManager::RD);

float RandomManager::GetRandomNumber() {
  return RNG.GetRandomNumber(default_engine);
}

float RandomManager::random_range(float min, float max) {
  float random_number = GetRandomNumber();
  random_number = static_cast<float>(math::wrap(random_number));
  return std::lerp(min, max, random_number);
}

}  // namespace rpg::math::random