#include <window\hud\hud_window.h>

#include <imgui.h>
namespace rpg::hud {
Window::Window(const std::string& name, float xpos, float ypos)
    : name(name), x(xpos), y(ypos) {}

void Window::Draw() {
  ImGui::Begin(this->name.c_str());

  for (auto& widget : widgets)
    widget->Draw();

  ImGui::End();
}

void Window::AddWidget(Widget* widget) {
  widgets.emplace_back(widget);
}

}  // namespace rpg::hud