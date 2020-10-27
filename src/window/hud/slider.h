#pragma once

#include <window/hud/widget.h>
#include <window/hud/label.h>

#include <string>
#include <functional>
namespace rpg::hud {
class Slider : public Label {
  enum class SliderType { INT, FLOAT };

  int* int_ptr;
  float* float_ptr;
  SliderType type;
  float max, min;

 public:
  Slider(const std::string& name, int* var, float min = 0.0f, float max = 1.0f);

  Slider(const std::string& name,
         float* var,
         float min = 0.0f,
         float max = 1.0f);

  Slider(const std::string& name,
         const std::string& label,
         float* var,
         float min = 0.0f,
         float max = 1.0f);

  void Draw();

  ~Slider(){};
};  // namespace rpg::hud
}  // namespace rpg::hud