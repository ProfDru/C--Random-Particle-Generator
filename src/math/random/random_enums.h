#pragma once

namespace rpg::math::random {
enum class RNG_Algorithm {
  DEFAULT = 0,
  MINSTD = 1,
  MT19937 = 2,
  RANLUX48 = 3,
  RANLUX48_B = 4,
  KNUTH = 6
};
}