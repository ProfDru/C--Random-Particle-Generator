#pragma once
#include <concepts>
#include <numeric>
#include <cassert>

namespace rpg::math {
template <typename T>
concept Vector3DStruct = requires(T a) {
  { a.x }
  ->std::convertible_to<double>;
  { a.y }
  ->std::convertible_to<double>;
  { a.z }
  ->std::convertible_to<double>;
};

template <typename T>
concept Vector3DArray = requires(T a) {
  { a[0] }
  ->std::convertible_to<double>;
  { a[1] }
  ->std::convertible_to<double>;
  { a[2] }
  ->std::convertible_to<double>;
};

template <typename T>
concept Vector3D = Vector3DStruct<T> || Vector3DArray<T>;

template <typename T>
concept Kinematic = requires {
  { T::pos }
  ->Vector3D;
  { T::vel }
  ->Vector3D;
};

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
}  // namespace rpg::math
