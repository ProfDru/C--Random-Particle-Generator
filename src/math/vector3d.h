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
concept Vector3DBoth = Vector3DArray<T>&& Vector3DStruct<T>;

template <typename T>
concept Vector3D = Vector3DStruct<T> || Vector3DArray<T>;

template <int i>
inline Numeric auto constexpr get(const Vector3DStruct auto& st) {
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
  }
}

template <int i>
inline constexpr Numeric auto get(const Vector3DArray auto& st) {
  return st[i];
}

template <int i>
inline constexpr Numeric auto get(const Vector3DBoth auto& st) {
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
  };
}

template <int i, Vector3DStruct T, Numeric N>
inline constexpr void set(T& st, N value) {
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
  }
}

template <int i, Vector3DArray T, Numeric N>
inline constexpr void set(T& st, N value) {
  st[i] = value;
}

template <int i>
inline constexpr void set(Vector3DBoth auto& st, Numeric auto value) {
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
  }
}

/*! \brief Convert 3 coordinates from a spherical coordinate system to a
 * cartesian coordinate system */
inline constexpr Vector3D auto spherical_to_cartesian(Vector3D auto coord) {
  const Numeric auto rho = get<0>(coord);
  const Numeric auto theta = get<1>(coord);
  const Numeric auto phi = get<2>(coord);

  const Numeric auto x = rho * sin(phi) * cos(theta);
  const Numeric auto y = rho * sin(phi) * sin(theta);
  const Numeric auto z = rho * cos(phi);

  return decltype(coord){x, y, z};
}

template <Vector3D T, Vector3D V>
inline constexpr Vector3D auto add(T v1, V v2) {
  const Numeric auto x = get<0>(v1) + get<0>(v2);
  const Numeric auto y = get<1>(v1) + get<1>(v2);
  const Numeric auto z = get<2>(v1) + get<2>(v2);

  return T{x, y, z};
}

template <Vector3D T, Vector3D V>
inline constexpr auto multiply(T v1, const V& v2) {
  const Numeric auto x = get(v1, 0) * get(v2, 0);
  const Numeric auto y = get(v1, 1) * get(v2, 1);
  const Numeric auto z = get(v1, 2) * get(v2, 2);

  return T{x, y, z};
}

template <Vector3D T, Numeric S>
inline constexpr auto multiply(T v1, S scalar) {
  const Numeric auto x = get<0>(v1) * scalar;
  const Numeric auto y = get<1>(v1) * scalar;
  const Numeric auto z = get<2>(v1) * scalar;

  return T{x, y, z};
}

template <Numeric T>
inline constexpr Numeric auto magnitude(T x, T y, T z) {
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

template <Vector3D T>
inline constexpr Numeric auto magnitude(const T& vector) {
  const auto x = get(vector, 0);
  const auto y = get(vector, 1);
  const auto z = get(vector, 2);

  return magnitude(x, y, z);
}

inline constexpr void normalize(Vector3D auto& v) {
  const Numeric auto mag = magnitude(v);

  set(v, 0, get(v, 0) / mag);
  set(v, 1, get(v, 1) / mag);
  set(v, 2, get(v, 2) / mag);
}

inline constexpr void set_magnitude(Vector3D auto& v,
                                    Numeric auto new_magnitude) {
  normalize(v);

  set(v, 0, get(v, 0) * new_magnitude);
  set(v, 1, get(v, 1) * new_magnitude);
  set(v, 2, get(v, 2) * new_magnitude);
}

}  // namespace rpg::math