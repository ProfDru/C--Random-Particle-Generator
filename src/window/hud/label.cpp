#include <window/hud/label.h>
#include <imgui.h>

namespace rpg::hud {

Label::Label(const std::string& name, const std::string& text)
    : name(name), text(text), is_automatic(false) {}

Label::Label(const std::string& name,
             std::function<std::string()> update_function)
    : name(name),
      text(""),
      string_function(update_function),
      is_automatic(true) {}

void Label::Draw() {
  if (is_automatic) {
    ImGui::Text(string_function().c_str());
  } else
    ImGui::Text(text.c_str());
}
}  // namespace rpg::hud