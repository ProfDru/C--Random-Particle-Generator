#include <window/hud/group.h>

#include <imgui.h>

namespace rpg::hud {

Group::Group(const std::string& name,
             const std::vector<Widget*> widgets,
             bool use_group)
    : name(name), use_group(use_group) {
  this->widgets =
      std::vector<std::unique_ptr<Widget>>(widgets.begin(), widgets.end());
}

void Group::Draw() {
  if (use_group) {
    // If this returns false, then this group is hidden, so it's contents
    // shouldn't be drawn
    if (!ImGui::TreeNode(this->name.c_str()))
      return;
  }
  for (auto& widget : widgets) {
    widget->Draw();
    widget->DrawHelpMarker();
  }

  if (use_group) {
    ImGui::TreePop();
  }
}
}  // namespace rpg::hud