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

enum class RNG_Distribution {
  UNIFORM = 0,
  NORMAL = 1,
  LOG_NORMAL = 2,
  EXTREME = 3
};
}  // namespace rpg::math::random