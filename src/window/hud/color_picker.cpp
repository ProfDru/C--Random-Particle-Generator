#include <window\hud\color_picker.h>

#include <imgui.h>

namespace rpg::hud {
ColorPicker::ColorPicker(const std::string& name, float* color_ptr)
    : color_ptr(color_ptr), name(name) {}

void ColorPicker::Draw() {
  ImGui::ColorPicker3(this->name.c_str(), this->color_ptr);
}
}  // namespace rpg::hud