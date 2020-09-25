#include <concepts>
#include <random>

namespace rpg::simulation {

template <class T>
class RandomNumberGen {
  static inline T random_engine = T(0.0, 1.0);

 public:
  template <typename D>
  static inline float GetRandomNumber(D& device) {
    return RandomNumberGen::random_engine(device);
  }
};

/*! \brief Manages the state of the current random number generator */
class RandomManager {
  static RandomNumberGen<std::uniform_real_distribution<>> RNG;
  inline static std::random_device RD;

 public:
  /*! \brief get a random number between 0 and 1 */
  static float GetRandomNumber();

  /*! \brief Calculate a random number between the range of min and max*/
  static float random_range(float min, float max);
};
}  // namespace rpg::simulation