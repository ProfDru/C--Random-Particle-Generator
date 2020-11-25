#pragma once
#include <math/vector3d.h>

#include <physics/base.h>

#include <array>
namespace rpg::physics {
using namespace rpg::math;

static const float gravitational_constant = 9.81;
static const std::array<float, 3> Fg = {0, -gravitational_constant, 0};

template <Vector3D K, Numeric seconds>
inline void apply_velocity(K& position, const K& velocity, seconds S) {
  change_over_time(position, velocity, S);
}

template <Vector3D K, Numeric seconds>
inline void apply_gravity(K& velocity, seconds s) {
  change_over_time(velocity, Fg, s);
}

inline void update_position_with_gravity(Vector3D auto& position,
                                         Vector3D auto& velocity,
                                         Numeric auto time) {
  const Vector3D auto gravity_accel =
      multiply(multiply(Fg, powf(time, 2)), 0.5f);
  const Vector3D auto change_due_to_velocity = multiply(velocity, time);

  position = add(add(position, change_due_to_velocity), gravity_accel);
  velocity = add(velocity, multiply(Fg, time));
}

inline constexpr Numeric auto kinematic_energy(Numeric auto velocity_magnitude,
                                               Numeric auto mass) {
  return (mass * pow(velocity_magnitude, 2) / static_cast<decltype(mass)>(2));
}

/*! \brief Calculate the current kinematic energy of a body */
inline constexpr Numeric auto kinematic_energy(const Vector3D auto& velocity,
                                               Numeric auto mass) {
  const Numeric auto velocity_magnitude = magnitude(velocity);
  return kinematic_energy(velocity_magnitude, mass);
}

inline constexpr Numeric auto velocity_from_kinematic_energy(
    Numeric auto kinematic_energy,
    Numeric auto mass) {
  return sqrt(2.0 * kinematic_energy / mass);
}

inline constexpr Numeric auto calculate_energy_loss(Numeric auto e) {
  return (1.0 - pow(e, 2));
}

}  // namespace rpg::physics