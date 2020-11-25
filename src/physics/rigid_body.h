
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

inline void set_grounded(RigidBody auto& body) {
  set<1>(body.velocity, 0);
  set<1>(body.pos, 0);
}

inline void bounce_basic(RigidBody auto& body,
                         Numeric auto mass = 5.0,
                         Numeric auto e = 0,
                         Numeric auto collision_pos = 0.0,
                         Numeric auto time_since_last_update = 0.0) {
  // Minimum velocity
  static const float grounded_threshold = 0.01f;

  // Return if there's no possible collision
  if (get<1>(body.pos) > collision_pos || get<1>(body.velocity) > 0)
    return;
  // Otherwise check if the particle should be grounded
  else if (get<1>(body.velocity) > -grounded_threshold) {
    set_grounded(body);
    return;
  }

  Numeric auto y_vel = abs(get<1>(body.velocity));
  Numeric auto time_since = time_since_last_update;
  const Numeric auto distance_underground =
      abs(collision_pos - get<1>(body.pos));
  const Numeric auto time_since_collision = distance_underground / y_vel;

  if (time_since_collision > time_since) {
    set_grounded(body);
    return;
  }

  // Rewind the particle to the time just before the point of collision
  physics::update_position_with_gravity(body.pos, body.velocity,
                                        -time_since_collision);

  // Calculate how much energy was lost with the bounce
  y_vel = get<1>(body.velocity);

  const Numeric auto energy = kinematic_energy(y_vel, mass);
  const Numeric auto energy_loss = calculate_energy_loss(e);
  const Numeric auto energy_after_bounce = energy - (energy_loss * energy);

  // Update the velocity of the body based on the new energy
  const double velocity_after_bounce =
      velocity_from_kinematic_energy(energy_after_bounce, mass);
  set<1>(body.velocity, velocity_after_bounce);

  // Now play the motion of the object since the time of impact with the new
  // velocity
  physics::update_position_with_gravity(
      body.pos, body.velocity,
      std::min(time_since_collision, time_since_last_update));
}
}  // namespace rpg::physics
