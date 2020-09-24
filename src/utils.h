#include <GLFW/glfw3.h>
#include <array>
#include <numeric>
namespace rpg {

static int window_width = 1280;
static int window_height = 720;

inline void WindowResizeCallback(GLFWwindow* window, int width, int height) {
  window_width = width;
  window_height = height;
}

struct Resolution {
  float width;
  float height;

  inline Resolution GetCenterPoint() {
    return Resolution{std::midpoint(0.0f, this->width),
                      std::midpoint(0.0f, this->height)};
  }
};

inline float CalculateAspectRatio() {
  return static_cast<float>(window_width) / static_cast<float>(window_height);
}

inline Resolution GetWindowResolution(GLFWwindow* win) {
  Resolution R;

  int width, height;
  glfwGetWindowSize(win, &width, &height);

  R.width = static_cast<float>(width);
  R.height = static_cast<float>(height);

  return R;
}

}  // namespace rpg
