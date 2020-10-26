#include <window/hud_manager.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace rpg {

const char* glsl_version = "#version 440";

std::unordered_map<std::string, hud::Window> HudManager::windows =
    std::unordered_map<std::string, hud::Window>();

void DrawWindow(const std::string& title) {
  ImGui::Begin(title.c_str());
  ImGui::Text("Hello World!");
  ImGui::End();
}

void HudManager::CreateWindow(const std::string& name,
                              float x_pos,
                              float y_pos,
                              bool is_hud) {
  HudManager::windows.insert(std::pair<std::string, rpg::hud::Window>{
      name, hud::Window(name, is_hud, x_pos, y_pos)});
}

void HudManager::AddWidget(const std::string& window_name,
                           hud::Widget* widget) {
  // throw if a window with this name doesn't exist
  if (windows.count(window_name) == 0)
    throw std::exception();

  windows.at(window_name).AddWidget(widget);
}

void HudManager::Init(GLFWwindow* win) {
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(win, false);
  ImGui_ImplOpenGL3_Init(glsl_version);
}

void HudManager::Draw() {
  // Create new frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // Call window code
  // DrawWindow("Settings");
  for (auto& win_pair : windows)
    win_pair.second.Draw(HudManager::enable);

  // Tell ImGUI to render then send that data to opengl
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool HudManager::KeyCallBack(int key, int mods) {
  return false;
}

bool HudManager::MouseClickCallback(int mouse_action, int mouse_button) {
  return false;
}
bool HudManager::MousePosCallback(int mouseX, int mouseY) {
  return false;
}
bool HudManager::ScrollWheelCallback(int pos) {
  return false;
}
bool HudManager::WindowResizecallback(int width, int height) {
  return false;
}

void HudManager::SetEnabled(bool draw) {
  HudManager::enable = draw;
}

}  // namespace rpg