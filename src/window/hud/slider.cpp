#include <window/hud/slider.h>

#include <imgui.h>

namespace rpg::hud {

Slider::Slider(const std::string& name, int* var, float min, float max)
    : Label(name, name), int_ptr(var), max(max), min(min) {
  this->type = SliderType::INT;
}

Slider::Slider(const std::string& name, float* var, float min, float max)
    : Label(name, name), float_ptr(var), max(max), min(min) {
  this->type = SliderType::FLOAT;
}

Slider::Slider(const std::string& name,
               const std::string& label,
               float* var,
               float min,
               float max)
    : Label(name, label), float_ptr(var), min(min), max(max) {
  this->type = SliderType::FLOAT;
}

void Slider::Draw() {
  switch (this->type) {
    case SliderType::FLOAT:
      ImGui::SliderFloat(this->text.c_str(), this->float_ptr, this->min,
                         this->max, "%.3f", 1);
      break;
    case SliderType::INT:
      ImGui::SliderInt(this->text.c_str(), this->int_ptr, this->min, this->max,
                       "%d", 1);
      break;
  }
}
}  // namespace rpg::hud