#pragma once

#include <window/hud/widget.h>
#include <window/hud/label.h>

#include <string>
#include <functional>

namespace rpg::hud {
class Slider : public Label {
  float* var;
  float min, max;
  // std::function<void(float)> callback;

 public:
  Slider(const std::string& name,
         const std::string& label,
         float* var,
         float min = 0.0f,
         float max = 1.0f);

  void Draw();

  ~Slider(){};
};
}  // namespace rpg::hud