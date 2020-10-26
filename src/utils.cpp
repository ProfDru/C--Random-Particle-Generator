#include <utils.h>

namespace rpg {

float Globals::window_height = 720;
float Globals::window_width = 1280;

void Globals::UpdateWindowSize(float width, float height) {
  window_width = width;
  window_height = height;
}

float Globals::CalculateAspectRatio() {
  return static_cast<float>(window_width) / static_cast<float>(window_height);
}

glm::vec2 Globals::ScreenCenter() {
  return glm::vec2{std::midpoint(0.0f, static_cast<float>(window_width)),
                   std::midpoint(0.0f, static_cast<float>(window_height))};
}

}  // namespace rpg