#pragma once
#include <glm/glm.hpp>

#include <array>
#include <numeric>
#include <iostream>
class GLFWwindow;

namespace rpg {
class Globals {
 public:
  static int window_width;
  static int window_height;

  static void UpdateWindowSize(int width, int height);
  static float CalculateAspectRatio();
  static glm::vec2 ScreenCenter();
};

}  // namespace rpg
