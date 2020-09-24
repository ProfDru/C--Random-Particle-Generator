#include <GLFW/glfw3.h>
#include <array>
#include <numeric>
namespace rpg {

struct Resolution {
  float width;
  float height;

  inline Resolution GetCenterPoint() {
    return Resolution{std::midpoint(0.0f, this->width),
                      std::midpoint(0.0f, this->height)};
  }
};
inline Resolution GetWindowResolution(GLFWwindow* win) {
  Resolution R;

  int width, height;
  glfwGetWindowSize(win, &width, &height);

  R.width = static_cast<float>(width);
  R.height = static_cast<float>(height);

  return R;
}

}  // namespace rpg
