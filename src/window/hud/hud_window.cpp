#include <window\hud\hud_window.h>

#include <imgui.h>
namespace rpg::hud {
Window::Window(const std::string& name, float xpos, float ypos)
    : name(name), x(xpos), y(ypos) {}

void Window::Draw() {
  ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);

  // Begin only returns true if the window isn't minimized
  if (ImGui::Begin(this->name.c_str())) {
    for (auto& widget : widgets) {
      widget->Draw();
      widget->DrawHelpMarker();
    }
  }
  ImGui::End();
}

void Window::AddWidget(Widget* widget) {
  widgets.emplace_back(widget);
}

}  // namespace rpg::hud