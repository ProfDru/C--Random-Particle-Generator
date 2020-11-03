#include <window/hud/checkbox.h>

#include <imgui.h>

namespace rpg::hud {
CheckBox::CheckBox(const std::string& name, bool* target)
    : name(name), target(target) {}

void CheckBox::Draw() {
  ImGui::Checkbox(name.c_str(), target);
}
}  // namespace rpg::hud