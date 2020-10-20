#include <window/hud/widget.h>

#include <imgui.h>

namespace rpg::hud {

void Widget::SetHelpMarker(const std::string& help_text) {
  this->help_marker = help_text;
}

void Widget::DrawHelpMarker() {
  if (!this->help_marker.empty()) {
    ImGui::SameLine();
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
      ImGui::BeginTooltip();
      ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
      ImGui::TextUnformatted(this->help_marker.c_str());
      ImGui::PopTextWrapPos();
      ImGui::EndTooltip();
    }
  }
}
}  // namespace rpg::hud