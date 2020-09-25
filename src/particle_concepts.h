#include <concepts>

template <typename T>
concept Vector3D = requires(T a) {
  a.x + a.y + a.z;
};

template <typename T>
concept Kinematic = requires {
  { T::pos }
  ->Vector3D;
  { T::vel }
  ->Vector3D;
};
