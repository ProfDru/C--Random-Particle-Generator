#pragma once
#include <system\bindings.h>

namespace rpg::input {

/*! \brief A set of bindings specifically for GLFW3 */
struct GLFW_binds {
  static Bindings binds;
};
}  // namespace rpg::input