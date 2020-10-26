#pragma once
#include <glm/glm.hpp>

#include <array>
#include <numeric>
#include <iostream>
class GLFWwindow;

namespace rpg {
class Globals {
 public:
  static float window_width;
  static float window_height;

  static void UpdateWindowSize(float width, float height);
  static float CalculateAspectRatio();
  static glm::vec2 ScreenCenter();
};

}  // namespace rpg
