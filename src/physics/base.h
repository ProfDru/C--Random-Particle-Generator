#pragma once

#include <math/vector3d.h>

namespace rpg::physics {
using namespace rpg::math;

inline void change_over_time(Vector3D auto& quantity,
                             const Vector3D auto& rate,
                             Numeric auto seconds) {
  const Vector3D auto change = multiply(rate, seconds);

  quantity = add(quantity, change);
}

}  // namespace rpg::physics