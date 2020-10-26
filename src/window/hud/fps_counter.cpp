#include <window/hud/fps_counter.h>
#include <imgui.h>

namespace rpg::hud {

FPSCounter::FPSCounter(const std::string& name) : Label(name, name) {
  this->name = name;
}

void FPSCounter::Draw() {
  ImGui::Text("Drawtime = %.3f ms/frame, %.1f FPS",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
}  // namespace rpg::hud