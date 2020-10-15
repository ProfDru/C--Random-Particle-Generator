#include <window/hud_manager.h>

#include <AntTweakBar.h>
namespace rpg {

void HudManager::Init() {
  TwInit(TW_OPENGL, NULL);
  HudManager::main_bar = TwNewBar(name.c_str());
}

bool HudManager::KeyCallBack(int key, int mods) {
  return TwKeyPressed(key, mods);
}

bool HudManager::MouseClickCallback(int mouse_action, int mouse_button) {
  return TwMouseButton(static_cast<TwMouseAction>(mouse_action),
                       static_cast<TwMouseButtonID>(mouse_button));
}
bool HudManager::MousePosCallback(int mouseX, int mouseY) {
  return TwMouseMotion(mouseX, mouseY);
}
bool HudManager::ScrollWheelCallback(int pos) {
  return TwMouseWheel(pos);
}
bool HudManager::WindowResizecallback(int width, int height) {
  //! \todo Can't find the function for this right now
  return true;
}

}  // namespace rpg