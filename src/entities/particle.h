#pragma once
#include <array>
namespace rpg {

struct Particle {
  using Vector3 = std::array<float, 3>;
  float lifetime;
  Vector3 pos;
  Vector3 color;
  Vector3 velocity;

  inline Particle()
      : lifetime(-1.0f),
        pos(Vector3{0, 0, 0}),
        color(Vector3{0, 0, 0}),
        velocity(Vector3{0, 0, 0}){};

  template <typename Vec>
  inline void set_color(const Vec& new_color) {
    color[0] = new_color[0];
    color[1] = new_color[1];
    color[2] = new_color[2];
  }
  template <typename Vec>
  inline void set_velocity(const Vec& new_velocity) {
    velocity[0] = new_velocity[0];
    velocity[1] = new_velocity[1];
    velocity[2] = new_velocity[2];
  }
};
}  // namespace rpg