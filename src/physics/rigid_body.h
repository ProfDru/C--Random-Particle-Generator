
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

enum class BODY_STATE { COLLIDING = 0, GROUNDED = 1, AIRBORNE = 2 };

constexpr inline BODY_STATE check_state(const Vector3D auto& pos,
                                        const Vector3D auto& velocity,
                                        float ground_pos) {
  const float grounded_threshold = 0.01f;
  const Numeric auto y_pos = get<1>(pos);
  const Numeric auto y_velocity = get<1>(velocity);

  const bool is_above_ground = y_pos > ground_pos;
  const bool has_upward_velocity = y_velocity > 0;
  const bool is_within_grounded_threshold = y_velocity > -grounded_threshold;

  if (is_above_ground || has_upward_velocity)
    return BODY_STATE::AIRBORNE;
  else if (is_within_grounded_threshold)
    return BODY_STATE::GROUNDED;
  else
    return BODY_STATE::COLLIDING;
}

inline void bounce_basic(RigidBody auto& body,
                         Numeric auto mass = 5.0,
                         Numeric auto e = 0,
                         Numeric auto collision_pos = 0.0,
                         Numeric auto time_since_last_update = 0.0) {
  // Minimum velocity
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
  const Numeric auto velocity_after_bounce =
      velocity_from_kinematic_energy(energy_after_bounce, mass);
  set<1>(body.velocity, velocity_after_bounce);

  // Now play the motion of the object since the time of impact with the new
  // velocity
  physics::update_position_with_gravity(
      body.pos, body.velocity,
      std::min(time_since_collision, time_since_last_update));
}

/*! \brief Full cycle physics step containing all phenomena */
inline void full_simulation_step(RigidBody auto& body,
                                 bool enable_bounce = true,
                                 Numeric auto mass = 5.0f,
                                 Numeric auto e = 0.0f,
                                 Numeric auto ground_pos = 0.0f,
                                 Numeric auto time = 0.0f) {
  // Update position based on velocity since this is always relevant
  const Vector3D auto change_due_to_velocity = multiply(body.velocity, time);
  body.pos = add(body.pos, change_due_to_velocity);
  apply_gravity(body.pos, body.velocity, time);
  const auto state = check_state(body.pos, body.velocity, ground_pos);

  switch (state) {
    case BODY_STATE::GROUNDED:
      set_grounded(body);
      break;
    case BODY_STATE::COLLIDING:
      if (enable_bounce) {
        bounce_basic(body, 0.5f, e, ground_pos, time);
      }
      break;
    case BODY_STATE::AIRBORNE:
      break;
  }
}
}  // namespace rpg::physics
