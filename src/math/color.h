#include <math/base.h>
#include <math/units.h>
#include <math/vector3d.h>

#include <functional>
#include <assert.h>
namespace rpg::math::color {
inline bool in_range(const Numeric auto val,
                     const Numeric auto min,
                     const Numeric auto max) {
  return (val >= min && val <= max);
}

/*! \brief Conver a color from a HSV color space to an RGB colorspace */
inline void hsv_to_rgb(Numeric auto& h, Numeric auto& s, Numeric auto& v) {
  assert(in_range(h, 0.0, 1.0) && in_range(s, 0.0, 1.0) &&
         in_range(v, 0.0, 1.0));

  h = h * 360.0;
  const double h_prime = h / 60.0;
  const double chroma = v * s;
  const double x = chroma * (1 - abs(std::fmod(h_prime, 2) - 1));

  const double m = v - chroma;

  if (h_prime <= 1) {
    h = chroma;
    s = x;
    v = 0;
  } else if (h_prime <= 2) {
    h = x;
    s = chroma;
    v = 0;
  } else if (h_prime <= 3) {
    h = 0;
    s = chroma;
    v = x;
  } else if (h_prime <= 4) {
    h = 0;
    s = x;
    v = chroma;
  } else if (h_prime <= 5) {
    h = x;
    s = 0;
    v = chroma;
  } else if (h_prime <= 6) {
    h = chroma;
    s = 0;
    v = x;
  }
  h += m;
  s += m;
  v += m;
}

/*! \brief Function for the alternate conversion of hsv to rgb*/
inline Numeric auto alt_function(Numeric auto n,
                                 Numeric auto h,
                                 Numeric auto s,
                                 Numeric auto v) {
  const Numeric auto k = std::abs(std::fmod((n + h / 60.0), 6.0));
  return v - v * s * std::max(0.0, std::min(std::min(k, 4.0 - k), 1.0));
}

/*! \brief A simplified implementation of HSV to rgb */
inline void hsv_to_rgb_simplified(Numeric auto& h,
                                  Numeric auto& s,
                                  Numeric auto& v) {
  assert(in_range(h, 0.0, 1.0) && in_range(s, 0.0, 1.0) &&
         in_range(v, 0.0, 1.0));

  h = h * 360.0;
  const Numeric auto H = h;
  const Numeric auto S = s;
  const Numeric auto V = v;
  h = alt_function(5.0, H, S, V);
  s = alt_function(3.0, H, S, V);
  v = alt_function(1.0, H, S, V);
}

/*! \brief Convert a vector3D to rgb */
inline void hsv_to_rgb(Vector3D auto& hsv_color) {
  Numeric auto h = get(hsv_color, 0);
  Numeric auto s = get(hsv_color, 1);
  Numeric auto v = get(hsv_color, 2);

  hsv_to_rgb_simplified(h, s, v);

  set(hsv_color, 0, h);
  set(hsv_color, 1, s);
  set(hsv_color, 2, v);
}

}  // namespace rpg::math::color