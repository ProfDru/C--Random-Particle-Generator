#include <utils.h>

namespace rpg {

int Globals::window_height = 720;
int Globals::window_width = 1280;

void Globals::UpdateWindowSize(int width, int height) {
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