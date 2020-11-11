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

/*! \brief A simple API to access the Uniform Random Number Generator.


  \remarks While this does not provide the flexibility or control of the new
  API, it is still useful in contexts where it is either not conveinent or
  possible to create new distributions frequently. The results for getting a
  random number between min and max will be less accurate, but faster than
  creating a new distribution between min and max if you were to only use it a
  few times.

 */
class GlobalRandom {
 public:
  static Generator rand_gen;
  static std::unique_ptr<Distribution> dist;

  /*! \brief Seed every random number engine in here */
  static void SeedEngines();

  /*! \brief Get a uniformly distributed random number between 0 and 1. */
  static float GetRandomNumber();

  /*! \brief Calculate a uniformly distributed number between min and max

    \note This will not be as accurate as it would be using the full random API
    since it is taking a result and lerping it over min and max instead of
    creating a new uniform distribution based on min and max.
   */
  static float GetRandomNumber(float min, float max);
};
}  // namespace rpg::math::random