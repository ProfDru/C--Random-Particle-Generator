
#include <physics/kinematics.h>
#include <math/vector3d.h>

#include <concepts>

namespace rpg::physics {
using namespace rpg::math;

template <typename T>
concept RigidBody = requires {
  { T::pos }
  ->Vector3D;
  { T::velocity }
  ->Vector3D;
};

inline void apply_gravity(RigidBody auto& body, Numeric auto seconds) {
  apply_gravity(body.velocity, seconds);
}

inline void apply_velocity(RigidBody auto& body, Numeric auto seconds) {
  apply_velocity(body.pos, body.velocity, seconds);
}

inline auto kinematic_energy(const RigidBody auto& body, Numeric auto mass) {
  return kinematic_energy(body.velocity, mass);
}

inline void bounce_basic(RigidBody auto& body,
                         Numeric auto mass = 5.0,
                         Numeric auto e = 0) {
  const Numeric auto energy = kinematic_energy(body, mass);

  const auto energy_loss = calculate_energy_loss(e);
  const auto energy_after_bounce = energy_loss * energy;

  const auto velocity_after_bounce =
      velocity_from_kinematic_energy(energy_after_bounce, mass);
  set_magnitude(body.velocity, velocity_after_bounce);
  set(body.velocity, 1, -get(body.velocity, 1));
}
}  // namespace rpg::physics
