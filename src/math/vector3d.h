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
auto get(int i, const T& st) {
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
inline Numeric auto get(const T& st, int i) {
  return st[i];
}

template <Vector3DStruct T, Numeric N>
inline constexpr void set(T& st, int i, N value) {
  switch (i) {
    case 0:
      st.x = value;
      break;
    case 1:
      st.y = value;
      break;
    case 2:
      st.z = value;
      break;
    default:
      assert(false);
      break;
  }
}

template <Vector3DArray T, Numeric N>
inline constexpr auto set(const T& st, int i, N value) {
  st[i] = value;
}

/*! \brief Convert 3 coordinates from a spherical coordinate system to a
 * cartesian coordinate system */
template <Vector3D T>
inline constexpr Vector3D auto spherical_to_cartesian(const T coord) {
  const Numeric auto rho = get(coord, 0);
  const Numeric auto theta = get(coord, 1);
  const Numeric auto phi = get(coord, 2);

  const Numeric auto x = rho * sin(phi) * cos(theta);
  const Numeric auto y = rho * sin(phi) * sin(theta);
  const Numeric auto z = rho * cos(phi);

  return T{x, y, z};
}

template <Vector3D T, Vector3D V>
inline auto add(const T& v1, const V& v2) {
  const Numeric auto x = get(v1, 0) + get(v2, 0);
  const Numeric auto y = get(v1, 1) + get(v2, 1);
  const Numeric auto z = get(v1, 2) + get(v2, 2);

  return T{x, y, z};
}

template <Vector3D T, Vector3D V>
inline auto multiply(const T& v1, const V& v2) {
  const auto x = get(v1, 0) * get(v2, 0);
  const auto y = get(v1, 1) * get(v2, 1);
  const auto z = get(v1, 2) * get(v2, 2);

  return T{x, y, z};
}

template <Vector3D T, Numeric S>
inline auto multiply(const T& v1, S scalar) {
  const auto x = get(v1, 0) * scalar;
  const auto y = get(v1, 1) * scalar;
  const auto z = get(v1, 2) * scalar;

  return T{x, y, z};
}

template <Numeric T>
auto magnitude(T x, T y, T z) {
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

template <Vector3D T>
auto magnitude(const T& vector) {
  const auto x = get(vector, 0);
  const auto y = get(vector, 1);
  const auto z = get(vector, 2);

  return magnitude(x, y, z);
}

inline void normalize(Vector3D auto& v) {
  const auto mag = magnitude(v);

  set(v, 0, get(v, 0) / mag);
  set(v, 1, get(v, 1) / mag);
  set(v, 2, get(v, 2) / mag);
}

inline void set_magnitude(Vector3D auto& v, Numeric auto new_magnitude) {
  normalize(v);

  set(v, 0, get(v, 0) * new_magnitude);
  set(v, 1, get(v, 1) * new_magnitude);
  set(v, 2, get(v, 2) * new_magnitude);
}

}  // namespace rpg::math