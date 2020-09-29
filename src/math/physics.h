#pragma once
#include <math/vector3d.h>

namespace rpg::math {
const double gravitational_constant = 9.81;

template <typename T>
concept Kinematic = requires {
  { T::pos }
  ->Vector3D;
  { T::velocity }
  ->Vector3D;
};

template <Kinematic K, Numeric seconds>
inline void apply_velocity(K& body, seconds S) {
  const Vector3D auto change_in_pos = multiply(body.velocity, S);

  body.pos = add(body.pos, change_in_pos);
}

template <Kinematic K, Numeric seconds>
inline void apply_gravity(K& body, seconds S) {
  // Cast G so we don't lose any precision
  auto g = static_cast<decltype(get(body.pos, 0))>(gravitational_constant);

  Vector3D auto gravity_to_add = decltype(body.pos){0, -1 * g * S, 0};
  body.velocity = add(body.velocity, gravity_to_add);
}

/*! \brief Calculate the current kinematic energy of a body */
template <Kinematic K, Numeric N = double>
inline auto kinematic_energy(const K& body, N mass = 5.0) {
  const auto velocity_magnitude = magnitude(body.velocity);
  return (mass * pow(velocity_magnitude, 2) / static_cast<N>(2));
}

template <Numeric N = double>
inline auto velocity_from_kinematic_energy(N kinematic_energy, N mass = 5.0) {
  return sqrt(2 * kinematic_energy / mass);
}

template <Kinematic K>
inline void bounce_basic(K& body, Numeric auto mass = 5.0, Numeric auto e = 0) {
  const auto energy = kinematic_energy(body);
  const auto energy_loss = (1 - pow(e, 2));
  const auto energy_after_bounce = energy_loss * energy;
  const auto velocity_after_bounce =
      velocity_from_kinematic_energy(energy_after_bounce, mass);
  set_magnitude(body.velocity, velocity_after_bounce);
  set(body.velocity, 1, -get(body.velocity, 1));
}

}  // namespace rpg::math