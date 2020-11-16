#pragma once

#include <random>
#include <math\random\generator.h>

namespace rpg::math::random {

class Distribution {
 public:
  /*! \brief Get a number within this distribution at the give number */
  virtual float get_number(Generator& in) = 0;

  virtual ~Distribution(){};
};
}  // namespace rpg::math::random