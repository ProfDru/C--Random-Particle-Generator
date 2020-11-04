
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
                         Numeric auto e = 0,
                         Numeric auto collision_pos = 0.0,
                         Numeric auto time_since_last_update = -1) {
  // Do nothing if the particle has no vertical momentum
  double time_since = static_cast<double>(time_since_last_update);
  double y_vel = abs(get(body.velocity, 1));
  if (y_vel < 0.001) {
    set(body.velocity, 1, 0);
    set(body.pos, 1, 0);

    return;
  }

  const double distance_underground = abs(collision_pos - get(body.pos, 1));
  const double time_since_collision = distance_underground / y_vel;

  // If time_since_last_update is unset, set it to time_since_collision to
  // remove the check entirely
  if (time_since == -1)
    time_since = time_since_collision;
  else if (time_since_collision > time_since)
    return;

  // Rewind the particle to the time just before the point of collision
  // physics::apply_velocity(body, -time_since_collision);
  // body.velocity = add(body.velocity, multiply(physics::Fg, -time_since));
  physics::update_position_with_gravity(body.pos, body.velocity,
                                        -time_since_collision);
  // Calculate how much energy was lost with the bounce
  y_vel = body.velocity.y;
  const double energy = kinematic_energy(y_vel, mass);
  const double energy_loss = calculate_energy_loss(e);
  const double energy_after_bounce = energy - (energy_loss * energy);

  // Update the velocity of the body based on the new energy
  const double velocity_after_bounce =
      velocity_from_kinematic_energy(energy_after_bounce, mass);
  set(body.velocity, 1, velocity_after_bounce);

  // Invert the y-direction of the velocity since it has bounced then
  // move the particle since it's bounce
  // set(body.velocity, 1, -get(body.velocity, 1));

  // replay the motion of the object since the time of impact with the new
  // velocity
  physics::update_position_with_gravity(body.pos, body.velocity,
                                        time_since_collision);
}  // namespace rpg::physics
}  // namespace rpg::physics
