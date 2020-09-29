#include <math_concepts.h>
#include <math.h>

namespace rpg::math {

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