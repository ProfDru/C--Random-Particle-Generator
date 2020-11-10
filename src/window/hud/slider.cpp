#include <window/hud/slider.h>

#include <imgui.h>

namespace rpg::hud {

Slider::Slider(const std::string& name,
               int* var,
               float min,
               float max,
               const std::string& help_text)
    : Label(name, name),
      int_ptr(var),
      max(max),
      min(min),
      type(SliderType::INT) {
  this->SetHelpMarker(help_text);
}

Slider::Slider(const std::string& name,
               float* var,
               float min,
               float max,
               const std::string& help_text)
    : Label(name, name),
      float_ptr(var),
      max(max),
      min(min),
      type(SliderType::FLOAT) {
  this->SetHelpMarker(help_text);
}

Slider::Slider(const std::string& name,
               const std::string& label,
               float* var,
               float min,
               float max,
               const std::string& help_text)
    : Label(name, label),
      float_ptr(var),
      min(min),
      max(max),
      type(SliderType::FLOAT) {
  this->SetHelpMarker(help_text);
}

void Slider::Draw() {
  if (this->same_line) {
    ImGui::SameLine();
  }
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