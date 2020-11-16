#pragma once

namespace rpg::math::random {
/*! \brief a unique integer ID for a random number generator from the
 * std::random library */
enum class RNG_Algorithm {
  DEFAULT = 0,
  MINSTD = 1,
  MT19937 = 2,
  RANLUX48 = 3,
  RANLUX48_B = 4,
  KNUTH = 6
};

/*! \brief A unique integer ID for a distribution of numbers from the
 * std::random library.*/
enum class RNG_Distribution {
  UNIFORM = 0,
  NORMAL = 1,
  LOG_NORMAL = 2,
  EXTREME = 3,
  WEIBULL = 4,
  CHI = 5,
  STUDENT = 6,
  FISHER = 7,
  GAMMA = 8,
  EXPONENTIAL = 9
};
}  // namespace rpg::math::random