#pragma once
#include <math/vector3d.h>

namespace rpg::math {
template <typename T>
concept Kinematic = requires {
  { T::pos }
  ->Vector3D;
  { T::vel }
  ->Vector3D;
};

}  // namespace rpg::math