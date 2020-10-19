#include <window/hud/slider.h>

#include <imgui.h>

namespace rpg::hud {
Slider::Slider(const std::string& name,
               const std::string& label,
               float* var,
               float min,
               float max)
    : Label(name, label), var(var), min(min), max(max) {}

void Slider::Draw() {
  ImGui::SliderFloat(this->text.c_str(), this->var, this->min, this->max, "",
                     1);
}
}  // namespace rpg::hud