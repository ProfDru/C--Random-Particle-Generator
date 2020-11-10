#pragma once
#include <math/random/random_enums.h>
#include <math/random/generator.h>
#include <math/random/distribution.h>

#include <memory>
namespace rpg {

/*! \brief Manages a random number generator/distribution or just holds a
   constant


    Used to make it easier to swap between constants and random numbers.*/
class RandomOrConstant {
 private:
  std::unique_ptr<math::random::Distribution> distribution;
  math::random::Generator generator;
  bool force_wrap;
  float gen_random_number();

 public:
  float constant, min_value, max_value;
  float rand_min, rand_max;

  math::random::RNG_Algorithm next_algorithm =
      math::random::RNG_Algorithm::DEFAULT;
  math::random::RNG_Distribution next_distribution =
      math::random::RNG_Distribution::UNIFORM;

  bool use_random = false;
  RandomOrConstant();

  /*! \brief Create a new random or constant  */
  RandomOrConstant(
      float constant,
      float min = 0.0f,
      float max = 1.0f,
      math::random::RNG_Algorithm alg = math::random::RNG_Algorithm::DEFAULT,
      math::random::Distribution* dist = nullptr,
      bool start_random = false,
      bool force_wrap = false);

  /*! \brief Change the random number generator.  */
  void set_generator(math::random::RNG_Algorithm alg);

  /*! \brief Change the distribution used for the random number generation */
  void set_distribution(math::random::Distribution* dist);

  /*! \brief Get a random number of get the distribution. */
  float get_number();
};
}  // namespace rpg