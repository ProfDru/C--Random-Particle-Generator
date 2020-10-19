#include <window/hud/label.h>
#include <imgui.h>

namespace rpg::hud {

Label::Label(const std::string& name, const std::string& text) {
  this->name = name;
  this->text = text;
}

void Label::Draw() {
  ImGui::Text(text.c_str());
}
}  // namespace rpg::hud