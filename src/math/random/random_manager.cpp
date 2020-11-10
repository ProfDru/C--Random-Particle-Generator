#include <math/random/random_manager.h>
#include <math/random/distributions/normal.h>

#include <cmath>
#include <algorithm>

namespace rpg::math::random {
Generator RandomManager::rand_gen(RNG_Algorithm::KNUTH);
std::unique_ptr<Distribution> RandomManager::dist =
    std::unique_ptr<Distribution>(new Normal(0.5, 0.5));

RandomNumberEngine<std::mt19937> RandomManager::mnt(RandomManager::RD);
RandomNumberEngine<std::minstd_rand> RandomManager::minstd(RandomManager::RD);
RandomNumberEngine<std::ranlux48> RandomManager::ranlux(RandomManager::RD);
RandomNumberEngine<std::ranlux48_base> RandomManager::ranlux_base(
    RandomManager::RD);
RandomNumberEngine<std::knuth_b> RandomManager::knuth_base(RandomManager::RD);
RandomNumberEngine<std::default_random_engine> RandomManager::default_engine(
    RandomManager::RD);

struct MinMax {
  float min;
  float max;
};

template <class T>
inline MinMax get_bounds(T& generator) {
  return MinMax{generator.min(), generator.max()};
}

inline MinMax get_min_and_max(RNG_Algorithm rng) {
  switch (rng) {
    case RNG_Algorithm::KNUTH:
      return get_bounds(RandomManager::knuth_base);
    case RNG_Algorithm::MINSTD:
      return get_bounds(RandomManager::minstd);
    case RNG_Algorithm::MT19937:
      return get_bounds(RandomManager::mnt);
    case RNG_Algorithm::RANLUX48:
      return get_bounds(RandomManager::ranlux);
    case RNG_Algorithm::RANLUX48_B:
      return get_bounds(RandomManager::ranlux_base);
    default:
      return get_bounds(RandomManager::default_engine);
  }
}

float random_range_impl(float min, float max, RNG_Algorithm rng) {
  const float random_number = RandomManager::GetRandomNumber(rng);
  return std::lerp(min, max, random_number);
}

float RandomManager::GetRandomNumber(RNG_Algorithm alg) {
  rand_gen.set_type(alg);
  return dist->get_number(rand_gen);
}

float RandomManager::GetRandomNumber(float min, float max, RNG_Algorithm rng) {
  return random_range_impl(min, max, rng);
}

}  // namespace rpg::math::random