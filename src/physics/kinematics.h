#pragma once
#include <math/vector3d.h>

#include <physics/base.h>

#include <array>
namespace rpg::physics {
using namespace rpg::math;

const double gravitational_constant = 9.81;
const std::array<double, 3> Fg = {0, -gravitational_constant, 0};

template <Vector3D K, Numeric seconds>
inline void apply_velocity(K& position, const K& velocity, seconds S) {
  change_over_time(position, velocity, S);
}

template <Vector3D K, Numeric seconds>
inline void apply_gravity(K& velocity, seconds s) {
  change_over_time(velocity, Fg, s);
}

inline auto kinematic_energy(Numeric auto velocity_magnitude,
                             Numeric auto mass) {
  return (mass * pow(velocity_magnitude, 2) / static_cast<decltype(mass)>(2));
}

/*! \brief Calculate the current kinematic energy of a body */
inline auto kinematic_energy(const Vector3D auto& velocity, Numeric auto mass) {
  const auto velocity_magnitude = magnitude(velocity);
  return kinematic_energy(velocity_magnitude, mass);
}

inline auto velocity_from_kinematic_energy(Numeric auto kinematic_energy,
                                           Numeric auto mass) {
  return sqrt(2 * kinematic_energy / mass);
}

inline constexpr auto calculate_energy_loss(Numeric auto e) {
  return (1 - pow(e, 2));
}

}  // namespace rpg::physics