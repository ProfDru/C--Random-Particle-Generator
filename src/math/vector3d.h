#pragma once
#include <math/base.h>
#include <math.h>

namespace rpg::math {

template <typename T>
concept Vector3DStruct = requires(T a) {
  { a.x }
  ->Numeric;
  { a.y }
  ->Numeric;
  { a.z }
  ->Numeric;
};

template <typename T>
concept Vector3DArray = requires(T a) {
  { a[0] }
  ->Numeric;
  { a[1] }
  ->Numeric;
  { a[2] }
  ->Numeric;
};

template <typename T>
concept Vector3D = Vector3DStruct<T> || Vector3DArray<T>;

template <Vector3DStruct T>
auto get_coordinate(int i, const T& st) {
  switch (i) {
    case 0:
      return st.x;
      break;
    case 1:
      return st.y;
      break;
    case 2:
      return st.z;
      break;
    default:
      assert(false);
      return std::numeric_limits<float>::infinity();
      break;
  }
}

template <Vector3DArray T>
auto get_coordinate(const T& st, int i) {
  return st[i];
}

/*! \brief Convert 3 coordinates from a spherical coordinate system to a
 * cartesian coordinate system */
template <Vector3D T>
inline auto spherical_to_cartesian(const T coord) {
  const auto rho = get_coordinate(coord, 0);
  const auto theta = get_coordinate(coord, 1);
  const auto phi = get_coordinate(coord, 2);

  const auto x = rho * sin(phi) * cos(theta);
  const auto y = rho * sin(phi) * sin(theta);
  const auto z = rho * cos(phi);

  return T{x, y, z};
}

}  // namespace rpg::math