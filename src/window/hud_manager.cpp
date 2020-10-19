#include <window/hud_manager.h>

namespace rpg {

void HudManager::SetParam(const std::string& param, const std::string& val) {}

void HudManager::Init(float window_x, float window_y) {}

void HudManager::Draw() {}

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

}  // namespace rpg