#pragma once
#include <concepts>
#include <numeric>
#include <cassert>

namespace rpg::math {

template <typename T>
concept Numeric = std::convertible_to<T, double>;

/*! \brief Get the normalized position of val between a and b */
template <Numeric T>
inline constexpr auto inverse_lerp(auto a, auto b, T val) {
  return ((abs(val) - a) / (b - a));
}

}  // namespace rpg::math
