#include <window\hud\hud_window.h>

#include <imgui.h>
namespace rpg::hud {
Window::Window(const std::string& name, bool is_hud, float xpos, float ypos)
    : is_hud(is_hud), name(name), x(xpos), y(ypos) {}

void Window::Draw(bool is_paused) {
  // Only draw if the game is paused or this is part of the heads up display
  if (is_paused || is_hud) {
    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);

    // Begin only returns true if the window isn't minimized
    if (ImGui::Begin(this->name.c_str(), NULL,
                     ImGuiWindowFlags_AlwaysAutoResize)) {
      for (auto& widget : widgets) {
        widget->Draw();
        widget->DrawHelpMarker();
      }
    }
    ImGui::End();
  }
}

void Window::AddWidget(Widget* widget) {
  widgets.emplace_back(widget);
}

}  // namespace rpg::hud