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
  const double x = chroma * (1.0 - abs(std::fmod(h_prime, 2.0) - 1.0));

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

inline void hsv_to_rgb_char(unsigned char& h,
                            unsigned char& s,
                            unsigned char& v) {
  const auto H = h;
  const auto S = s;
  const auto V = v;

  const auto region = h / 43;
  const auto remainder = (h - (region * 43)) * 6;

  const auto p = (v * (255 - s)) >> 8;
  const auto q = (v * (255 - ((s * remainder) >> 8))) >> 8;
  const auto t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

  switch (region) {
    case 0:
      h = V;
      s = t;
      v = p;
      break;
    case 1:
      h = q;
      s = V;
      v = p;
      break;
    case 2:
      h = p;
      s = V;
      v = t;
      break;
    case 3:
      h = p;
      s = q;
      v = V;
      break;
    case 4:
      h = t;
      s = p;
      v = V;
      break;
    default:
      h = V;
      s = p;
      v = q;
      break;
  }
}

inline unsigned char double_to_char(double f) {
  return static_cast<unsigned char>(f * 255.0);
}

inline float char_to_double(unsigned char c) {
  return static_cast<double>(c) / 255.0;
}

inline void hsv_to_rgb_char(Numeric auto& h, Numeric auto& s, Numeric auto& v) {
  auto H = double_to_char(h);
  auto S = double_to_char(s);
  auto V = double_to_char(v);

  hsv_to_rgb_char(H, S, V);

  h = char_to_double(H);
  s = char_to_double(S);
  v = char_to_double(V);
}

/*! \brief Convert a vector3D to rgb */
inline void hsv_to_rgb(Vector3D auto& hsv_color) {
  Numeric auto h = get<0>(hsv_color);
  Numeric auto s = get<1>(hsv_color);
  Numeric auto v = get<2>(hsv_color);

  hsv_to_rgb_char(h, s, v);

  set<0>(hsv_color, h);
  set<1>(hsv_color, s);
  set<2>(hsv_color, v);
}

}  // namespace rpg::math::color