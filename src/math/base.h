#pragma once
#include <concepts>
#include <numeric>
#include <cassert>
#include <algorithm>

namespace rpg::math {

template <typename T>
concept Numeric = std::convertible_to<T, double>;

/*! \brief Get the normalized position of val between a and b */
inline constexpr auto inverse_lerp(Numeric auto a,
                                   Numeric auto b,
                                   Numeric auto val) {
  auto aa = static_cast<decltype(val)>(a);
  auto bb = static_cast<decltype(val)>(b);

  val = std::clamp(val, aa, bb);
  return ((abs(val) - aa) / (bb - aa));
}

/*! \brief Wrap the number from 0.0 to 1.0 */
inline constexpr double wrap(Numeric auto& num) {
  return num - std::floor(num);
}

}  // namespace rpg::math
