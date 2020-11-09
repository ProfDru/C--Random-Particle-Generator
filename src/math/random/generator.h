#pragma once
#include <math/random/random_enums.h>
#include <random>
#include <variant>

namespace rpg::math::random {
using REngine = std::variant<std::mt19937,
                             std::minstd_rand,
                             std::ranlux48,
                             std::ranlux48_base,
                             std::knuth_b,
                             std::default_random_engine>;
using gen_t = int64_t;

/*! \brief Provides access to one of many random number generator algorithms
            defined in the standard library. */
class Generator {
 private:
  std::random_device device;
  REngine reng;
  RNG_Algorithm alg;

  /*! \brief Reseed the random number engine */
  void seed_engine();

 public:
  Generator(RNG_Algorithm alg = RNG_Algorithm::DEFAULT);

  /*! \brief Get the type of algorithm this generator uses */
  RNG_Algorithm get_type() const;

  /*! \brief Advance the state of the generator and create return the random
   * number */
  gen_t get_rand();

  /*! \brief Advance the state of the generator and create the random number*/
  gen_t operator()();

  /*! \brief Set the type of algorithm this generator uses

    If `alg` is already being used, nothing will happen.
  */
  void set_type(RNG_Algorithm alg);

  gen_t min() const;
  gen_t max() const;
};

}  // namespace rpg::math::random