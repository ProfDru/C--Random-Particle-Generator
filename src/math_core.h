#pragma once
#include <math_concepts.h>
#include <numeric>
#include <numbers>
#include <ratio>

namespace rpg::math {

template <typename T>
constexpr T dtor_conv_factor() {
  return static_cast<T>(std::numbers::pi) / static_cast<T>(180.0);
}

template <typename T>
constexpr T rtod_conv_factor() {
  return static_cast<T>(180.0) / static_cast<T>(std::numbers::pi);
}

template <std::floating_point T>
inline constexpr auto to_radians(T num_in_degrees) {
  const auto conv_factor = dtor_conv_factor<T>();

  return conv_factor * num_in_degrees;
}

template <std::integral T, std::floating_point F = double>
inline constexpr auto to_radians(T num_in_degrees) {
  return to_radians(static_cast<F>(num_in_degrees));
}
}  // namespace rpg::math