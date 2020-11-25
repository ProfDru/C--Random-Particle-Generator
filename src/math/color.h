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

inline std::array<unsigned char, 3> hsv_to_rgb_char(unsigned char h,
                                                    unsigned char s,
                                                    unsigned char v) {
  const unsigned char region = h / 43;
  const unsigned char remainder = (h - (region * 43)) * 6;

  const unsigned char p = (v * (255 - s)) >> 8;
  const unsigned char q = (v * (255 - ((s * remainder) >> 8))) >> 8;
  const unsigned char t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

  switch (region) {
    case 0:
      return {v, t, p};
      break;
    case 1:
      return {q, v, p};
      break;
    case 2:
      return {p, v, t};
      break;
    case 3:
      return {p, q, v};
      break;
    case 4:
      return {t, p, q};
      break;
    default:
      return {v, p, q};
      break;
  }
}

inline unsigned char float_to_char(Numeric auto f) {
  return static_cast<unsigned char>(f * 255.0f);
}
inline float char_to_float(unsigned char f) {
  return static_cast<float>(f) / 255.0f;
}

inline auto hsv_to_rgb_char(Numeric auto h, Numeric auto s, Numeric auto v) {
  const auto H = float_to_char(h);
  const auto S = float_to_char(s);
  const auto V = float_to_char(v);

  const std::array<unsigned char, 3> rgb = hsv_to_rgb_char(H, S, V);

  return std::array<decltype(h), 3>{char_to_float(rgb[0]),
                                    s = char_to_float(rgb[1]),
                                    v = char_to_float(rgb[2])};
}

/*! \brief Convert a vector3D to rgb */
inline void hsv_to_rgb(Vector3D auto& hsv_color) {
  Numeric auto h = get<0>(hsv_color);
  Numeric auto s = get<1>(hsv_color);
  Numeric auto v = get<2>(hsv_color);

  const auto rgb = hsv_to_rgb_char(h, s, v);

  set<0>(hsv_color, rgb[0]);
  set<1>(hsv_color, rgb[1]);
  set<2>(hsv_color, rgb[2]);
}

}  // namespace rpg::math::color