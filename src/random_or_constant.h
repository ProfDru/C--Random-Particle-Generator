#pragma once
#include <math/random/random_enums.h>
#include <math/random/generator.h>
#include <math/random/distribution.h>

#include <memory>
namespace rpg {

/*!
     \brief Manages a random number generator/distribution as well as a constant
   value.

    \remarks
   Used to make it easier to swap between constants and random numbers at
   runtime. Each instance of RandomOrConstant has its own random number
   generator that is fully independent from the results of every other random
   number generator.

   \note Depending on the distribution used, numbers may be greater or less
   than the provided min or max values.

   \todo Rename min and max to parameter 1 and parameter 2, since the function
   of these variables canges with each distribution

   \todo Support wrapping values between min_value and max_value

   \todo Support automatically getting the absolute value when calling
   get_number
*/
class RandomOrConstant {
 private:
  std::unique_ptr<math::random::Distribution>
      distribution;  //> A pointer to the current distribution
  math::random::Generator
      generator;  //> The internal random number generator unique to this ROC
  bool force_wrap;

  /*! \brief Generate a random number using the current distribution and
   * generator */
  float gen_random_number();

 public:
  float constant, min_value, max_value;
  float rand_min, rand_max;
  float scale_factor = 1;

  math::random::RNG_Algorithm next_algorithm =
      math::random::RNG_Algorithm::DEFAULT;
  math::random::RNG_Distribution next_distribution =
      math::random::RNG_Distribution::UNIFORM;

  bool use_random = false;
  RandomOrConstant();

  /*! \brief Create a new random or constant.

    \param constant Constant value for when in constant mode
    \param min Lower bound for random value when in random mode
    \param max Upper bound for random value when in random mode
    \param alg RNG_Algorithm to start with.
    \param dist RNG_Distribution to start with
    \param start_random If true, return random numbers upon construction
    otherwise only return the constant value.

   */
  RandomOrConstant(
      float constant,
      float min = 0.0f,
      float max = 1.0f,
      math::random::RNG_Algorithm alg = math::random::RNG_Algorithm::DEFAULT,
      math::random::Distribution* dist = nullptr,
      bool start_random = false);

  /*! \brief Change the random number generator.  */
  void set_generator(math::random::RNG_Algorithm alg);

  /*! \brief Change the distribution used for the random number generation */
  void set_distribution(math::random::Distribution* dist);

  /*! \brief Generate a random number based on the current distribution and
   * random number generator. */
  float get_number();
};
}  // namespace rpg