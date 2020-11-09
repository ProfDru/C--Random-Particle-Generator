#pragma once
#include <concepts>
#include <random>
#include <algorithm>
#include <math/random/random_enums.h>
#include <math/random/generator.h>
#include <math/random/distribution.h>
#include <memory>

#include <math/base.h>

namespace rpg::math::random {

template <class T>
class RandomNumberDistribution {
  static inline T random_engine = T(0, 1);

 public:
  template <typename D>

  static inline float GetRandomNumber(D& device) {
    const auto number = RandomNumberDistribution::random_engine(device);
    return number;
  }
};

template <class Engine>
class RandomNumberEngine {
  Engine E;

 public:
  inline RandomNumberEngine(std::random_device& d) : E(d()) {}

  inline auto min() { return E.min(); }
  inline auto max() { return E.max(); }
  inline auto operator()() { return E(); }
};  // namespace rpg::math::random

/*! \brief Manages the state of the current random number generator */
class RandomManager {
  static RandomNumberDistribution<std::uniform_real_distribution<>> RNG;

  // static RandomNumberEngine<std::mt19937_64> mnt_64;

 public:
  inline static std::random_device RD;
  static RandomNumberEngine<std::mt19937> mnt;
  static RandomNumberEngine<std::minstd_rand> minstd;
  static RandomNumberEngine<std::ranlux48> ranlux;
  static RandomNumberEngine<std::ranlux48_base> ranlux_base;
  static RandomNumberEngine<std::knuth_b> knuth_base;
  static RandomNumberEngine<std::default_random_engine> default_engine;
  static Generator rand_gen;
  static std::unique_ptr<Distribution> dist;

  /*! \brief Seed every random number engine in here */
  static void SeedEngines();

  /*! \brief get a random number between 0 and 1 */
  static float GetRandomNumber(RNG_Algorithm alg = RNG_Algorithm::DEFAULT);

  /*! \brief Calculate a random number between the range of min and max*/
  static float GetRandomNumber(float min,
                               float max,
                               RNG_Algorithm alg = RNG_Algorithm::DEFAULT);
};
}  // namespace rpg::math::random