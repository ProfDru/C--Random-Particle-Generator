#include <concepts>
#include <random>
#include <algorithm>
#include <math/base.h>

namespace rpg::simulation {

template <class T>
class RandomNumberGen {
  static inline T random_engine = T(1);

 public:
  template <typename D>

  static inline float GetRandomNumber(D& device) {
    const auto number = RandomNumberGen::random_engine(device);
    return number;
  }
};

/*! \brief Manages the state of the current random number generator */
class RandomManager {
  static RandomNumberGen<std::extreme_value_distribution<>> RNG;
  inline static std::random_device RD;

 public:
  /*! \brief get a random number between 0 and 1 */
  static float GetRandomNumber();

  /*! \brief Calculate a random number between the range of min and max*/
  static float random_range(float min, float max);
};
}  // namespace rpg::simulation