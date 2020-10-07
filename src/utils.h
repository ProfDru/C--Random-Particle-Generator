#pragma once
#include <glm/glm.hpp>

#include <array>
#include <numeric>
class GLFWwindow;

namespace rpg {

static int window_width = 1280;
static int window_height = 720;

inline void WindowResizeCallback(GLFWwindow* window, int width, int height) {
  window_width = width;
  window_height = height;
}

inline float CalculateAspectRatio() {
  return static_cast<float>(window_width) / static_cast<float>(window_height);
}

inline glm::vec2 ScreenCenter() {
  return glm::vec2{std::midpoint(0.0f, static_cast<float>(window_width)),
                   std::midpoint(0.0f, static_cast<float>(window_height))};
}

}  // namespace rpg
